var express = require('express')
var router = express.Router()



router.post('/', function(req, res) {
  
  
  switch(req.body.operation) {
    case "+":
        if(req.body.rowsA === req.body.rowsB && req.body.colsA === req.body.colsB) {
          break;
        } else {
          res.send(JSON.stringify({"cerr": "Invalid operation: number of rows and columns of matrix A don't match those of matrix B"}));
          return 0;
        };
    case "-":
        if(req.body.rowsA === req.body.rowsB && req.body.colsA === req.body.colsB) {
          break;
        } else {
          res.send(JSON.stringify({"cerr": "Invalid operation: number of rows and columns of matrix A don't match those of matrix B"}));
          return 0;
        };
    case "*":
        if(req.body.colsA === req.body.rowsB) {
          break;
        } else {
          res.send(JSON.stringify({"cerr": "Invalid operation: number of columns of matrix A don't match the number of rows of matrix B"}));
          return 0;
        };
    default:
        res.send(JSON.stringify({"cerr": "Error: invalid operator"}));
        return 0;
  };
  
  
  // Create the argument vectors "argv" to pass in as command line arguments to the C++ 
  // executable. In node.js the arguments must be in an array and this array is placed as
  // the second argument in starting the executable.
  // var argv = req.body.matrix;
  
  var argv = [req.body.operation, req.body.rowsA, req.body.colsA, ...req.body.matrixA, req.body.rowsB, req.body.colsB, ...req.body.matrixB];
  
  // Instantiate a child process using the exceFile method which runs the executable in 
  // the same shell as the node.js server.
  var execFile = require('child_process').execFile;
    
  // The C++ program to be run.
  var program = "/Users/nick/Documents/CompSci/WebDevelopment/matrixCalculator/cpp/matrixCalculator/matrixCalculator";

  // Run the C++ executable in the child process. Note: the first argument is the command 
  // used to run the program, the second argument is the arguments to be supplied to the
  // the program (on the command line these are normal entered directly next to the 
  // program run command with each argument separated by a space), the third argument is 
  // the function to be called when the executable has terminated.
    
  var child = execFile(program, argv, function (error, stdout, stderr) {
    if (error) {
      return response.status(500).send(error);
    }
  	if(stderr) {
      var response = {"cerr": stderr};
      res.send(JSON.stringify(response));
    }
    else {
      var result = stdout.split(",")
      var operation = result[0];
      result.splice(0, 1);
      
      var data = result.map((x) => Number(x));   // This is a string and is the content of everything passed to std::cout
        				                           // it is formatted as: operation,rows,cols,matrix[0],...,matrix[n]
      var rows = data[0];
      var cols = data[1];
      var matrix = data.slice(2, data.length);
      var response = {"cerr":"null", "operation":operation, "rows":rows, "cols":cols, "matrix": matrix};
      res.send(JSON.stringify(response));
    }
  });
});

module.exports = router