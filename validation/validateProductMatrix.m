%This function is used in validating the accuracy of my
%multiplySparseMatrices function.
%@param m1_name - the name of the input file for the dense matrix of the left hand operand
%@param m2_name - the name of the input file for the dense matrix of the right hand operand
%@param my_p_name - the name of the input file for the dense matrix of the calculated product
%@param output_name - the name of the file to write the results of the test
function [] = validateProductMatrix(m1_name, m2_name, my_p_name, output_name)
   	
	%set tolerance
	tol = 0.00001;
	
	%parse matrices
	m1 = parseMatrix(m1_name);
	m2 = parseMatrix(m2_name);
	my_p = parseMatrix(my_p_name);
	output = fopen(output_name, 'w');
		
	%multiply matrices
	p = m1 * m2;
	
	%compare result
	result = (abs(p - my_p));
	
	%check for discrepencies
	for i = 1:length(p)
		for j = 1:length(p)
			if (result(i,j) >= tol)
				fprintf(output, 'validation failed\n');
				exit;
			end
		end
	end
	
	fprintf(output, 'validation successful\n');
	fclose(output);
  
end

%This function pars the matrix from the input file with name name
%@param name - the name of the input file to parse
%return - the parse dense matrix
function [m] = parseMatrix(name)
    	%open file
	input = fopen(name, 'r');
    	
	%scan in size of data
	n = fscanf(input, '%d', [1,1]);
    	size = [n, n];

	%scan in data
    	m = fscanf(input, '%lf, ', size);
	
        %Matlab stores matrices column ordered to the result
        %must be transposed
	m = m';

    	fclose(input);
  
end
