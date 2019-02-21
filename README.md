# Generic-Cpp-Matrix-Class
Templated Matrix class for C++. Includes functions for determinant, inverse, transpose, and trace
<p>This class is designed for use in data analytics, but is templated to be used with any data type. Please note that the mathematical operators require basic operators (+,-,*,/) to function.</p>
<p>Matrices of this class can be operated on with any standard operator including those with equals (+=,-=,*=,/=). All operators can be used in conjuction with another Matrix or with a scalar of the data type the Matrix is templated for.</p>
<p>Matrices can be added to using insertRow and insertCol. Data within the matrix can be accessed via <i>var_name</i>[j][i] or <i>var_name</i>.get(j,i). Data should be set using <i>var_name</i>.set(j,i,new_data)</p>
<p>Included math operators are dot product, determinant, inverse, transpose, and trace.</p>
<b>Exceptions thrown:</b>
<p>Depending on the operation being performed, the following custom exceptions may be thrown: InvalidDimensions, NotInvertable, DivideByZero, BadData, and OutOfBounds. Additional information can be found in the exception object's what().</p>
