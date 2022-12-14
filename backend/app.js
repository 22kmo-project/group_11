const helmet = require('helmet');
const cors = require('cors');
var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');
const jwt = require('jsonwebtoken');

var userRouter = require('./routes/user');
var bankcardRouter = require('./routes/bankcard');
var loginRouter = require('./routes/login');
var bank_accountRouter = require('./routes/bank_account');
var transactionsRouter = require('./routes/transactions');
var bank_account_bank_cardRouter = require('./routes/bank_account_bank_card');
var bank_operationsRouter = require('./routes/bank_operations');


var app = express();

app.use(helmet());
app.use(cors());
app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

//SUOJAAMATTOMAT ENDPOINTIT
app.use('/user', userRouter);
app.use('/login', loginRouter);
app.use('/bankcard', bankcardRouter);
app.use('/bank_account', bank_accountRouter);
app.use('/transactions', transactionsRouter);
app.use('/bank_account_bank_card', bank_account_bank_cardRouter);
app.use('/bank_operations', bank_operationsRouter);


app.use(authenticateToken);
//SUOJATUT ENDPOINTIT


function authenticateToken(req, res, next) { 
    const authHeader = req.headers['authorization']
    const token = authHeader && authHeader.split(' ')[1]
  
    console.log("token = "+token);
    if (token == null) return res.sendStatus(401)
  
    jwt.verify(token, process.env.MY_TOKEN, (err, user) => {
      console.log(err)
  
      if (err) return res.sendStatus(403)
  
      req.user = user
  
      next()
    })
  }


module.exports = app;
