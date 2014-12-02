#!/usr/bin/python
import cgi
import csv
def checkUser(newUser):
	users = []
	with open('Members.csv', 'rb') as csvfile:

		reader = csv.reader(csvfile, delimiter=',', quotechar='|')
		for x in reader:
	 		if newUser == x[1] :
	 		 	return 1
	 	pass
	return 0
	pass
def updateInventory(product , qty):
	

	with open('Inventory.csv', 'rb') as csvfile:
		reader = csv.reader(csvfile, delimiter=',', quotechar='|')
		for x in reader:
	 		p1NAME=(x[0])
	 		p1PRICE=(float(x[1]))
	 		p1QTY=(int(x[2]))
	 		p2NAME=(x[3])
	 		p2PRICE=(float(x[4]))
	 		p2QTY=(int(x[5]))
	 		p3NAME=(x[6])
	 		p3PRICE=(float(x[7]))
	 		p3QTY=(int(x[8]))
	 		break;

	 		
	sub = int(qty) 
	name = ""
	price = 0.0
	if (product == 1) :
		name = p1NAME
		price = p1PRICE
		if (p1QTY - sub >= 0):
			p1QTY = p1QTY -sub
			pass
		else:
			return 0 
		pass
	if (product == 2) :
		name = p2NAME
		price = p2PRICE
		if (p2QTY - sub >= 0):
			p2QTY = p2QTY-sub
			pass
		else:
			return 0
		pass
	if (product == 3) :
		name = p3NAME
		price = p3PRICE
		if (p3QTY - sub >= 0):
			p3QTY = p3QTY-sub
			pass
		else:
			return 0 
		pass
	writer = csv.writer(open("Inventory.csv", "wb"))
	writer.writerow([p1NAME,p1PRICE,p1QTY,p2NAME,p2PRICE,p2QTY,p3NAME,p3PRICE,p3QTY])
	return 1,name,price
	pass
def printOrder(price,qty, name,productName):
	products = ["T-Shirt(s)","Hoodie(s)","Mittens"]
	print """
	
	<h1>"""
	print "Thank You ", name
	print """.</h1>
	  <h2>Transaction details</h2>
	  <p> you bought """
	print qty
	print "of" 
	print productName 
	print "at a price of $"
	print price
	print""" (CAD) </p>
	  <p> Your order total comes to $"""
	print qty*price
	print""" (CAD) </p>
	    <ul> <a href="../index.html">Home </a> </ul>"""
	
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
try:
	form = cgi.FieldStorage()
	confirm =  int(form.getvalue("confirm"))
	message = form.getvalue("message", "(no message)")
	price = float(form.getvalue("price"))
	qty = int(form.getvalue("Qty"))
	productName = int(form.getvalue("product"))
	username=form.getvalue("username").strip()

	productInfo = updateInventory(productName,qty)
 	pass
except Exception, e:
 	printError()
 	pass
if(checkUser(username) == 1 and  qty >= 1 and  confirm == 1 and productInfo[0]==1):
	printOrder(productInfo[2],qty,username,productInfo[1])
	pass
else:
	printError()

print """</html>""" 
cgi.escape(message)