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
	p1= 0
	p2= 0
	p3= 0
	with open('Inventory.csv', 'rb') as csvfile:
		reader = csv.reader(csvfile, delimiter=',', quotechar='|')
		for x in reader:
	 		p1= int(x[0])
	 		p2= int(x[1])
	 		p3= int(x[2])
	 	pass
	productNum = int(product)
	sub = int(qty) 
	if (productNum == 1) :
		if (p1 - sub >= 0):
			p1 = p1-sub
			pass
		else:
			return 0 
		pass
	if (productNum == 2) :
		if (p2 - sub >= 0):
			p2 = p2-sub
			pass
		else:
			return 0
		pass
	if (productNum == 3) :
		if (p3 - sub >= 0):
			p3 = p3-sub
			pass
		else:
			return 0 
		pass

	writer = csv.writer(open("Inventory.csv", "wb"))
	writer.writerow([p1,p2,p3])
	return 1
	pass
def printOrder(price,qty, name,productName):
	products = ["T-Shirt(s)","Hoodie(s)","Mittens"]
	print """
	
	<h1>"""
	print "Thank You ", username
	print """</h1>
	  <h2>Transaction details</h2>
	  <p> you bought """
	print qty
	print "of" 
	print products[int(productName)-1]  
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
	productName = form.getvalue("product")
	username=form.getvalue("username").strip()
 	pass
except Exception, e:
 	
 	printError()
 	pass

if(checkUser(username) == 1 and  qty >= 1 and  confirm == 1 and updateInventory(productName,qty)==1):
	printOrder(price,qty,username,productName)
	pass
else:
	printError()

print """</html>""" 
cgi.escape(message)