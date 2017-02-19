



var buttonEvaluate = document.querySelector('input[type="button"]');
var buttonOperators = document.querySelectorAll('.operatorSelector input[type="radio"]');

buttonEvaluate.addEventListener("click", getMatrices);

for(var i = 0; i < buttonOperators.length; ++i) {
  buttonOperators[i].addEventListener("change", changeOperatorSelection);
}

//Ensure only one operation can be selected
function changeOperatorSelection() {
  for(var i = 0; i < buttonOperators.length; ++i) {
    if(this === buttonOperators[i]) {
    
    } else {
      buttonOperators[i].checked = false;
    }
  }
}




function getOperatorSelection() {
  for(var i = 0; i < buttonOperators.length; ++i) {
    if(buttonOperators[i].checked === true) {
       return buttonOperators[i].value
    }
  }
}



function requestPost (data, action) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if(this.readyState == 4 && this.status == 200) {
      action(this.response);
    }
  }
  var request = JSON.stringify(data);
  xhttp.open("POST", "/calculator", true);
  xhttp.setRequestHeader("Content-type", "application/json; charset=utf-8");
  xhttp.send(request);
}



function displayResponse(res) {
  var response = JSON.parse(res);
  if(response.cerr === "null") {
    var matrixThree = document.querySelector('#matrix_three table');
    document.querySelector('#matrix_three p').innerHTML = "";
    var content = "";
    for(var i = 0; i < response.rows; ++i) {
      content += "<tr>";
      for(var j = 0; j < response.cols; ++j) {
        content += "<td>" + response.matrix[(i * response.cols) + j] + "</td>";
      }
      content += "</tr>";
    }
    matrixThree.innerHTML = content;
    } else {
    document.querySelector('#matrix_three p').innerHTML = response.cerr;
  }
  
}

function getMatrices() {

  
  
  var matrixOneLength = document.querySelectorAll('#matrix_one input[type="number"]').length;
  var matrixOne = document.querySelectorAll('#matrix_one input[type="number"]');
  var data = {};
  
  if(getOperatorSelection()) {
    document.querySelector(".operatorSelector p").innerHTML = "";
    data.operation = getOperatorSelection();
  } else {
    document.querySelector(".operatorSelector p").innerHTML = "Please select an operation.";
    return 0;
  }
  
  data.rowsA = document.querySelectorAll('#matrix_one tr').length;
  data.colsA = document.querySelector('#matrix_one tr').querySelectorAll('td').length;
  data.matrixA = [];
  
  for(var i = 0; i < matrixOneLength; ++i) {
    data.matrixA.push(matrixOne[i].valueAsNumber);
  }
  
  var matrixTwoLength = document.querySelectorAll('#matrix_two input[type="number"]').length;
  var matrixTwo = document.querySelectorAll('#matrix_two input[type="number"]');
  data.rowsB = document.querySelectorAll('#matrix_two tr').length;
  data.colsB = document.querySelector('#matrix_two tr').querySelectorAll('td').length;
  data.matrixB = [];
  
  for(var i = 0; i < matrixTwoLength; ++i) {
    data.matrixB.push(matrixTwo[i].valueAsNumber);
  }
  
  //JSON.stringify(data);
  requestPost(data, displayResponse);
}



//================Reshape Alt Meth=================

$('document').ready(function () {
  $('.matrix_dimensions input[type="range"]').change( function() {
    var currentRows = $(this).parent().parent().children("table").children("tbody").children("tr").length;
    var currentCols = $(this).parent().parent().children("table").children("tbody").children("tr:last").children("td").length;
    var dimName = this.name;
    var dimValue = this.value;    
    var id = $(this).parent().siblings("table").attr("id");


    if(dimName === 'rows') {
      if(dimValue > currentRows) {
        for(var i = 0; i < (dimValue - currentRows); ++i) { 
          $(`#${id} tbody`).append('<tr></tr>');
          var content = "";
          for(var j = 0; j < currentCols; ++j) {
            content += "<td><input type='number'></input></td>";
          }
          $(`#${id} tbody tr:last`).html(content);
        }
      }
      else if(dimValue < currentRows) {
        for(var j = 0; j < (currentRows - dimValue); ++j) {
            $(`#${id} tbody tr:last`).remove();
        }
      }
    }
    
    else if(dimName === 'cols') {
      if(dimValue > currentCols) {
        for(var i = 1; i <= currentRows; ++i) {
          var content = "";
          for(var j = 0; j < dimValue - currentCols; ++j) {
            content += "<td><input type='number'></input></td>";
          }
          $(`#${id} tbody tr:nth-of-type(${i})`).append(content);
        }
      }
      else if(dimValue < currentCols) {
        console.log("CP4");
        for(var i = 1; i <= currentRows; ++i) {
          for(var j = 0; j < currentCols - dimValue; ++j) {
            $(`#${id} tbody tr:nth-of-type(${i}) td:last`).remove();
          }
        }
      }
    };
  });
});



//=================Reshape Alt Meth END==============








