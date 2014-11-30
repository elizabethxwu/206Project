#!/usr/bin/python
import cgi
import csv
def checkUser(newUser):
	users = []
	with open('loggedin.csv', 'rb') as csvfile:
		reader = csv.reader(csvfile, delimiter=',', quotechar='|')
		for x in reader:
	 		if newUser == x[0] :
	 		 	return 1
	 	pass
	return 0
	pass
def updateInventory(product , qty):
	p1= 0
	p2= 0
	p3= 0
	with open('Inventory.csv', 'rb') as csvfile:
		reader = csv.reader(csvfile, delimiter=',', quotechar='|')
		for x in reader:
	 		p1= x[0]
	 		p2= x[1]
	 		p3= x[2]
	 	pass
	if (int(product) == 1) :
		if (p1 - qty >= 0):
			p1 = p1-qty
			pass
		else:
			return 0 
		pass
	if (int(product) == 2) :
		if (p2 - qty >= 0):
			p2 = p2-qty
			pass
		else:
			return 0 
		pass
	if (int(product) == 3) :
		if (p3 - qty >= 0):
			p3 = p3-qty
			pass
		else:
			return 0 
		pass
	with open('Inventory.csv', 'w',newline='') as csvfile:
		writer = csv.writer(csvfile, delimiter=',', quotechar='|')
		writer.writerow(p1,p2,p3)
	 	pass
	return 1
	pass
def printOrder(price,qty, name,productName):
	print """
	<head>
	<meta charset="utf-8">
	<meta http-equiv="X-UA-Compatible" content="IE=edge">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<title>Comp 206 Project</title>
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.1/css/bootstrap.min.css">
	<!-- HTML5 shim and Respond.js for IE8 support of HTML5 elements and media queries -->
	<!--[if lt IE 9]>
	<script src="https://oss.maxcdn.com/html5shiv/3.7.2/html5shiv.min.js"></script>
	<script src="https://oss.maxcdn.com/respond/1.4.2/respond.min.js"></script>
	<![endif]-->
	</head>
	<nav class="navbar navbar-inverse navbar-fixed-top" role="navigation">
	<div class="container">
	<div class="navbar-header">
	  <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#navbar" aria-expanded="false" aria-controls="navbar">
	    <span class="sr-only">Toggle navigation</span>
	    <span class="icon-bar"></span>
	    <span class="icon-bar"></span>
	    <span class="icon-bar"></span>
	  </button>
	  <a class="navbar-brand" href="#">Group Project</a>
	</div>
	<div id="navbar" class="navbar-collapse collapse">
	  
	</div><!--/.navbar-collapse -->
	</div>
	</nav>
	<!-- Main jumbotron for a primary marketing message or call to action -->
	<div class="jumbotron">
	<div class="container">
	<h1>"""
	print "Thank You ", username
	print """</h1>
	</div>
	</div>
	</nav>
	<div class="container">
	<!-- Example row of columns -->
	<div class="row">
	<div class="col-md-4">
	  <h2>Transaction details</h2>
	  <p> you bought """
	print qty," of ",productName 
	print """ at a price of """
	print price
	print""" (CAD) </p>
	  <p> Your order total comes to """
	print qty*price
	print""" (CAD) </p>"""
	
	pass
def printError():
	print "an error occured, please make sure you are logged in."
	pass
print "Content-type: text/html"
print
print """<html>
<head><title>Transaction details</title></head>
</html>
""" 
form = cgi.FieldStorage()
confirm =  int(form.getvalue("confirm"))
message = form.getvalue("message", "(no message)")
price = float(form.getvalue("price"))
qty = int(form.getvalue("Qty"))
productName = form.getvalue("product")
username=form.getvalue("username")

if(checkUser(username) == 1 and  qty >= 1 and  confirm == 1 and updateInventory(productName,qty)==1):
	printOrder(price,qty,username,productName)
	pass

else:
	printError()

print """</html>""" 
cgi.escape(message)