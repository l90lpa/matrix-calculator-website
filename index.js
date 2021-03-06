var express = require('express');
var parser = require('body-parser');
var app = express();


app.use(express.static('public'));    //This sends the public dir with all responses.

app.use(parser.json());

app.get('/', function (request, response) {    //Display homepage.
	response.sendFile(__dirname + '/views/index.html');
});

app.use('/calculator', require('./calculator'));

app.listen(process.env.PORT || 8080, function () {
	if(process.env.PORT) {
		console.log(process.env.PORT);
	}
	console.log('Running on 8080');
});

//app.listen(8080, function () {
//	console.log('Running on 8080');
//});
