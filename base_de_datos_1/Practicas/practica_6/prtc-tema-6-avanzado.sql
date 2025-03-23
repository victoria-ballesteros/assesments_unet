SET SERVEROUTPUT ON;

-- 1
CREATE OR REPLACE PROCEDURE empleados_top_n (n IN NUMBER) 
IS
    CURSOR cur_empleados IS 
        SELECT apellido, salario 
        FROM emple 
        ORDER BY salario DESC 
        FETCH FIRST n ROWS ONLY;
    v_apellido emple.apellido%TYPE;
    v_salario emple.salario%TYPE;
BEGIN
    OPEN cur_empleados;
    LOOP
        FETCH cur_empleados INTO v_apellido, v_salario;
        EXIT WHEN cur_empleados%NOTFOUND;
        DBMS_OUTPUT.PUT_LINE('Apellido: ' || v_apellido || ', Salario: ' || v_salario);
    END LOOP;
    CLOSE cur_empleados;
END;
/

BEGIN

empleados_top_n(10);

END;
/

-- 2
CREATE OR REPLACE PROCEDURE aumentar_salario (
    p_dept_no IN NUMBER,
    p_importe IN NUMBER,
    p_porcentaje IN NUMBER,
    p_total_aumento OUT NUMBER
) 
IS
    v_aumento NUMBER := 0;
BEGIN
    UPDATE emple
    SET salario = salario + 
        CASE 
            WHEN salario * (p_porcentaje / 100) > p_importe THEN salario * (p_porcentaje / 100)
            ELSE p_importe 
        END
    WHERE dept_no = p_dept_no
    RETURNING SUM(CASE WHEN salario * (p_porcentaje / 100) > p_importe THEN salario * (p_porcentaje / 100)
                        ELSE p_importe 
                    END) INTO p_total_aumento;
END;
/

DECLARE

cantidad_modificada NUMBER;

BEGIN

aumentar_salario(10, 300, 0.20, cantidad_modificada);
DBMS_OUTPUT.PUT_LINE('Aumento total: ' || cantidad_modificada);

END;
/

-- 3

CREATE OR REPLACE PROCEDURE actualizar_localidad (
    p_dept_no IN NUMBER,
    p_nueva_localidad IN VARCHAR2
) 
IS
BEGIN
    UPDATE depart
    SET loc = p_nueva_localidad
    WHERE dept_no = p_dept_no;
    
    IF SQL%ROWCOUNT = 0 THEN
        RAISE_APPLICATION_ERROR(-20001, 'No existe el departamento especificado.');
    END IF;
END;
/

BEGIN

actualizar_localidad(10, 'Petare');

END;
/

-- 4

CREATE OR REPLACE FUNCTION obtener_apellido (p_emp_no IN NUMBER) 
RETURN VARCHAR2 
IS
    v_apellido emple.apellido%TYPE;
BEGIN
    SELECT apellido INTO v_apellido 
    FROM emple 
    WHERE emp_no = p_emp_no;
    RETURN v_apellido;
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        RETURN 'Empleado no encontrado';
END;
/

BEGIN

DBMS_OUTPUT.PUT_LINE('Apellido del empleado indicado: ' || obtener_apellido(7698));

END;
/

-- 5

CREATE OR REPLACE PROCEDURE obtener_info_empleado (
    p_emp_no IN NUMBER,
    p_apellido OUT emple.apellido%TYPE,
    p_oficio OUT emple.oficio%TYPE,
    p_salario OUT emple.salario%TYPE
) 
IS
BEGIN
    SELECT apellido, oficio, salario 
    INTO p_apellido, p_oficio, p_salario 
    FROM emple 
    WHERE emp_no = p_emp_no;
END obtener_info_empleado;
/

DECLARE
    v_apellido emple.apellido%TYPE;
    v_oficio emple.oficio%TYPE;
    v_salario emple.salario%TYPE;
BEGIN
    obtener_info_empleado(7782, v_apellido, v_oficio, v_salario);
    DBMS_OUTPUT.PUT_LINE('Apellido: ' || v_apellido);
    DBMS_OUTPUT.PUT_LINE('Oficio: ' || v_oficio);
    DBMS_OUTPUT.PUT_LINE('Salario: ' || v_salario);
END;
/

-- 6

CREATE OR REPLACE FUNCTION salario_anual (
    p_salario_mensual IN NUMBER,
    p_comision IN NUMBER
) 
RETURN NUMBER 
IS
BEGIN
    RETURN (p_salario_mensual * 12) + p_comision;
END;
/

DECLARE
    v_salario_anual NUMBER;
    v_salario_mensual NUMBER := 800;  -- Valor de ejemplo
    v_comision NUMBER := 500;  -- Valor de ejemplo
BEGIN
    v_salario_anual := salario_anual(v_salario_mensual, v_comision);
    
    IF v_salario_anual < 10000 THEN
        v_salario_mensual := v_salario_mensual * 1.10;  -- Aumentar 10%
    END IF;

    DBMS_OUTPUT.PUT_LINE('Nuevo salario mensual: ' || v_salario_mensual);
END;
/

-- 7

CREATE TABLE auditar_emple (
    auditoria VARCHAR2(200)
);

CREATE OR REPLACE TRIGGER trg_auditar_emple
AFTER INSERT OR DELETE ON emple
FOR EACH ROW
BEGIN
    IF INSERTING THEN
        INSERT INTO auditar_emple (auditoria)
        VALUES (TO_CHAR(SYSDATE, 'DD-MM-YYYY HH24:MI:SS') || ' - Empleado ' || :NEW.emp_no || ' INSERTADO');
    ELSIF DELETING THEN
        INSERT INTO auditar_emple (auditoria)
        VALUES (TO_CHAR(SYSDATE, 'DD-MM-YYYY HH24:MI:SS') || ' - Empleado ' || :OLD.emp_no || ' ELIMINADO');
    END IF;
END;
/

INSERT INTO EMPLE VALUES (8698,'NEGRO','DIRECTOR',7839,TO_DATE('01/05/1981', 'DD/MM/YYYY'), 370500,NULL,30);


-- 8a. Procedimiento para generar mensaje de error
CREATE OR REPLACE PROCEDURE validar_horario AS
BEGIN
    RAISE_APPLICATION_ERROR(-20001, 'Usted solo puede modificar la data durante horario normal de oficina');
END;
/

-- 8b. Trigger que llama el procedimiento anterior
CREATE OR REPLACE TRIGGER trg_validar_horario
BEFORE INSERT OR UPDATE OR DELETE ON emple
BEGIN
    IF TO_CHAR(SYSDATE, 'HH24:MI') NOT BETWEEN '08:00' AND '18:00' THEN
        validar_horario;
    END IF;
END;
/

INSERT INTO EMPLE VALUES (9999,'NEGRO','DIRECTOR',7839,TO_DATE('01/05/1981', 'DD/MM/YYYY'), 370500,NULL,30);

