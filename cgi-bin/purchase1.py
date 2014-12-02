#!/usr/bin/python
import cgitb
import csv
cgitb.enable(display=0)

def checkUser(newUser):
	users = []
	if newUser == "NULL":
		return 0
		pass
	with open('Members.csv', 'rb') as csvfile:

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
	 		p1= int(x[0])
	 		p2= int(x[1])
	 		p3= int(x[2])
	 	pass
	productNum = int(product)
	productsQty = [p1,p2,p3]
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
	productsIMG = ["t.jpg","sweat.jpg","mitten.jpg"]
	print """
	<head>
	
	<title>Comp 206 Project</title>
	
	</head>
	
	<h1>"""
	print "Thank You ", username
	print """</h1>"""
	print "<img src=../%s>" % productsIMG[productName-1]
	print """
	  <h2>Transaction details</h2>
	  <p> you bought """
	print qty," of ",products[productName-1]  
	print """ at a price of """
	print price
	print""" (CAD) </p>
	  <p> Your order total comes to """
	print qty*price
	print""" (CAD) </p>"""
	pass
def printError():
	products = ["T-Shirt(s)","Hoodie(s)","Mittens"]

	print "an error occured, please make sure you are logged in and that there is ample QTY of your selection.\n There are "
	productsQTY = []
	with open('Inventory.csv', 'rb') as csvfile:
		reader = csv.reader(csvfile, delimiter=',', quotechar='|')
		for x in reader:
	 		productsQTY.append( int(x[0]))
	 		productsQTY.append( int(x[1]))
	 		productsQTY.append( int(x[2]))
	 	pass
	
	
	print "%s : %s --" % (productsQTY[0], products[0])
	print "%s : %s --" % (productsQTY[1], products[1])
	print "%s : %s ." % (productsQTY[2], products[2])
	print "\n please go back and try again."
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
productName = int(form.getvalue("product"))
username=form.getvalue("username")
print username
# confirm =  1
# price = 10
# qty = 10
# productName = 1
# confirm   int(form.getvalue("confirm"))
#message = form.getvalue("message", "(no message)")
# price = float(form.getvalue("price"))
# qty = int(form.getvalue("Qty"))
# productName = int(form.getvalue("product"))
# username=form.getvalue("username")
if(checkUser(username) == 1 and updateInventory(productName,qty)==1 and  qty >= 1 and  confirm == 1 ):
	printOrder(price,qty,username,productName)
	pass
else:
	printError()

print """</html>""" 
cgi.escape()