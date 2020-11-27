// system modules
const path 		 = require('path');
const fs 		 = require('fs');
const open 		 = require('child_process');
const express 	 = require('express');
const session 	 = require('express-session');
const bodyParser = require('body-parser');
const multer     = require('multer');

const storage    = multer.diskStorage({
	destination: (req, file, cb) =>{	
		cb(null, 'storage/shared');
	},
	filename: (req,file,cb) =>{
		cb(null, file.originalname, console.log(file))
	}
});


const upload = multer({ storage:storage });
const { spawn } = require('child_process'); // use for running programs/script/application (async) at the server
const fileserver = express();

// engine for user session
fileserver.use(session({
	secret: 'secret',
	resave: true,
	saveUninitialized: true
}));

fileserver.set('view engine', 'ejs');

fileserver.use((req,res,next) => {
	let filename = path.basename(req.url);
	let extension = path.extname(filename);

	if(req.session.loggedin === true){	

		let urlPath  = (`${req.url}`.substring(0,14));
		let filePath = (`/storage/shared`);

		if(urlPath === filePath){
			// get the date and time when a request is recorded
			let date_ob = new Date();
			let day 	= ("0" + date_ob.getDate()).slice(-2);
			let month 	= ("0" + (date_ob.getMonth() + 1)).slice(-2);
			let year 	= date_ob.getFullYear();

			let hours 	= date_ob.getHours();
			let minutes = date_ob.getMinutes();
			let seconds = date_ob.getSeconds();

			//write the log in a txt file in the server
			fs.writeFile(`${__dirname}/logs/downloads.txt`, `\n${req.session.username}\t\t--> ${year}/${month}/${day} - ${hours}:${minutes}:${seconds} ...REQUESTED=${filename}`, {flag: 'a+'},(err) => {
				if(err)
					console.log("error logging user");
			});
		}
	}
	next();
});

fileserver.use(express.static('storage'));
fileserver.use(express.static('public'));

fileserver.use(bodyParser.urlencoded({extended : true}));
fileserver.use(bodyParser.json());


fileserver.get('/files/', (req,res) => {
	res.sendFile(path.join(`${__dirname}/public/html/welcome.html`));
});

fileserver.post('/files/login-guest', (req,res) => {
	let user  = req.body.username;
	if(user.length < 3)
		res.send("Username Invalid : use alphanumeric characters, user name length : 4 characters and above");
	else{
		let program = spawn('html_generate',[]);
			program.stdout.on('data', (data) =>{
			let store = data.toString();
			console.log(store);
		});
		// session record
		req.session.username = user;
		req.session.loggedin = true;
		res.redirect('/files/login-guest');
	}
});

fileserver.post('/files/login-guest', (req,res) => {
	let user  = req.body.username;
	if(user.length < 3)
		res.send("Username Invalid : use alphanumeric characters, user name length : 4 characters and above");
	else{
		let program = spawn('html_generate',[]);

		req.session.username = user;
		req.session.loggedin = true;
		res.redirect('/files/login-guest');
	}
});

fileserver.get('/files/login-guest', (req,res) => {
	if(req.session.loggedin === true){
		let program = spawn('html_generate',[]);

		let date_ob = new Date();
		let day 	= ("0" + date_ob.getDate()).slice(-2);
		let month 	= ("0" + (date_ob.getMonth() + 1)).slice(-2);
		let year 	= date_ob.getFullYear();

		let hours 	= date_ob.getHours();
		let minutes = date_ob.getMinutes();
		let seconds = date_ob.getSeconds();

		fs.writeFile(`${__dirname}/logs/downloads.txt`, `\n${req.session.username}\t\t--> ${year}/${month}/${day} - ${hours}:${minutes}:${seconds}`, {flag: 'a+'},(err) => {
			if(err) {
				console.log("error logging user");
			}
			else
				console.log("Login log recorded");
		});
		res.render('guestview.ejs',{userName: `${req.session.username}`});
	}
	else
		res.send('login first as a guest');
});

let MAX_NUM_FILE = 1000000;
fileserver.post('/files/login-guest/upload', upload.array('selectedFile', MAX_NUM_FILE), (req, res, next) =>{

	const files = req.files;
	if(!files){
		const error = new Error('please choose files');
		error.httpStatusCode = 400;
		return next(error);
	}
	res.redirect('/files/login-guest');

	// also runs the c++ program in the background that will alter the html file to display uploaded files
	let program = spawn('html_generate',[]);
	program.stdout.on('data', (data) =>{
		let store = data.toString();
		console.log(store);
	});
	res.end();
});

'use strict';

const {networkInterfaces} = require('os');

const nets = networkInterfaces();
const results = Object.create(null);

for(const name of Object.keys(nets)){
	for(const net of nets[name]){
		if(net.family === 'IPv4' && !net.internal){
			if (!results[name]){
				results[name] = [];
			}
			results[name].push(net.address);
		}
	}
	
}

console.log("USE THE PROPER IP ADDRESS TO CONNECT WITH OTHER DEVICES");
console.log("\nif you want to share your files with other devices that is connected in you wi-fi");
console.log("use that address in the browser of the other device to access your files\n")
console.log("HOST_IP(s):")
console.log(results);
console.log("\nTo use input 'http://HOST_IP/files' or just 'HOST_IP/files' on other devices browser");
console.log("\nEXAMPLE ONLY : http://192.168.5.2/files")
fileserver.listen(80,console.log('FILE SERVER: STARTED')); // http 















