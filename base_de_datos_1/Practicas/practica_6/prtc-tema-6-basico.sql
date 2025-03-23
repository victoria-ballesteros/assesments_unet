SET SERVEROUTPU ON;

-- 1. Visualizar el apellido y el salario de los empleados
DECLARE
    CURSOR cur_emp IS SELECT apellido, salario FROM emple;
    v_apellido emple.apellido%TYPE;
    v_salario emple.salario%TYPE;
BEGIN
    OPEN cur_emp;
    LOOP
        FETCH cur_emp INTO v_apellido, v_salario;
        EXIT WHEN cur_emp%NOTFOUND;
        DBMS_OUTPUT.PUT_LINE('Apellido: ' || v_apellido || ', Salario: ' || v_salario);
    END LOOP;
    CLOSE cur_emp;
END;
/

-- 2. Actualizar el monto de comisión basado en el salario
DECLARE
    v_emp_id emple.emp_no%TYPE := &emp_no;
    v_salario emple.salario%TYPE;
    v_comision emple.comision%TYPE;
BEGIN
    SELECT salario INTO v_salario FROM emple WHERE emp_no = v_emp_id;

    IF v_salario IS NULL THEN
        v_comision := 0;
    ELSIF v_salario < 10000 THEN
        v_comision := v_salario * 0.10;
    ELSIF v_salario BETWEEN 10000 AND 15000 THEN
        v_comision := v_salario * 0.20;
    ELSE
        v_comision := v_salario * 0.20;
    END IF;

    UPDATE emple SET comision = v_comision WHERE emp_no = v_emp_id;
    COMMIT;
    DBMS_OUTPUT.PUT_LINE('Comisión actualizada: ' || v_comision);
END;
/

-- 3. Obtener y mostrar los nombres de los departamentos
DECLARE
    TYPE t_departamentos IS TABLE OF depart.dnombre%TYPE;
    v_departamentos t_departamentos;
BEGIN
    -- Obtener los nombres de los departamentos sin duplicados
    SELECT DISTINCT d.dnombre BULK COLLECT INTO v_departamentos 
    FROM emple e
    JOIN depart d ON e.dept_no = d.dept_no;

    -- Recorrer los departamentos y mostrarlos
    FOR i IN 1..v_departamentos.COUNT LOOP
        DBMS_OUTPUT.PUT_LINE('Departamento: ' || v_departamentos(i));
    END LOOP;
END;
/
