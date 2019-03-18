#!/usr/bin/python
'''
sophie.py
Adam Biglow
Date: 01/23/10

Facebook Puzzle Master Problem: Sophie
'''

import sys
import string

# Takes the second arguement from the command line (ie. one after python filename)
fileName = sys.argv[1]

readFile = open(fileName,"r")
linesArr = readFile.readlines()
readFile.close()

# get number of locations
numNodes = int(linesArr[0])

# get number of paths
numPaths = int(linesArr[numNodes+1])


# Dictionary of locations as ints
nodeDict = {}
# The probability of each location
nodeProb = [ None ] * numNodes

# This loop creates dictionary matching location name with number in nodeDict
# This also populates the probablity table nodeProb.
for node in range(1, numNodes+1):
	# Strips out new line or tab characters if there are any
	linesArr[node] = linesArr[node].replace( "\t","" ).replace( "\n","" )
	# Splits the string by the spaces	
	loc = linesArr[node].split(" ")
	
	# Set the respected values from the current line
	# Added extra functionality to handle extra spaces in file
	firstItem = False
	for x in loc:
		
		if( len(x) > 0):
			if( firstItem == False):
				nodeDict[ x ] = node-1
				firstItem = True
			else:
				nodeProb[ node - 1 ] = float( x )
				break;


# Create the empty adjanency matrix with appropriate size
adjMatrix = []
for x in range(numNodes):
	adjMatrix.append([])
	for y in range(numNodes):
		
		if x==y:
			adjMatrix[x].append(0)
		else:
			adjMatrix[x].append("inif")

# Loop puts all of the weights in the adjanency matrix
for path in range(numNodes + 2, numNodes + numPaths + 2):
	linesArr[path] = linesArr[path].replace( "\t","" ).replace( "\n","" )
	loc = linesArr[path].split(" ")

	# Add weight to approperiate spots in adjancency matrix
	# Added extra functionality to handle extra spaces in file
	firstItem = False
	secondItem = False
	for x in loc:
		if( len(x) > 0):
			if( firstItem == False):
				a = nodeDict[x]
				firstItem = True
			elif( secondItem == False):
				b = nodeDict[x]
				secondItem = True
			else:
				c = x
				break;

	adjMatrix[a][b] = float( c ) 
	adjMatrix[b][a] = float( c )


# I know for fact path time would not be greater than 2*Minimum spanning tree 
# Looked into Dijkstra shortest path algorithm but it seemed it would need a lot of work to change
# Found Floyd-Warshall's algorithm which seems to do a lot more especially with what I already have

# My work around for Floyd-Warshall since it should contain infinity as a weight
# but didn't want to spend too much time finding Python's version of infinity
def minimum(x, y, z):
	if( y == "inif" or z == "inif" ):
		return x
	elif( x == "inif" or int(x) > int(y) + int(z) ):
		return int(y) + int(z)
	else:
		return x

# Floyd-Warshall Alg
for k in range(0,numNodes):
	for i in range (0,numNodes):
		for j in range (0,numNodes):				
			adjMatrix[i][j] = minimum(adjMatrix[i][j], adjMatrix[i][k], adjMatrix[k][j])

#for x in adjMatrix:
#	print str(x)

# Now I have my adjacency matrix with the shortest path between every point
# I must now device a way of going to each node starting at 0 that will
# minimize the expected value
# can see an opitmal sub-structure
# Must make sure all nodes have been reached at some point
# Keep track of best expected value
# if expect value of path is greater that best expected value stop that path

# Sets the nodes visited to none and bestev time to none
nodeVisit = [ False ] * numNodes
bestEvTime = float(-1)

# resursive function for finding best expected value
def findEv( curNode, curProb, curEv):
	# grabs all global varibles that will be used
	global bestEvTime 
	global nodeVisit
	global nodeProb
	global adjMatrix

	# variable which will say if each node has been reached
	couldBeBest = True

	# since we are visiting it right now
	nodeVisit[curNode] = True
	
	# decrements the current probably of finding sophie
	curProb -= nodeProb[curNode]
	
	# Goes through each of the nodes that are attached to curNode
	for k in range(0, numNodes):
		# Checks for the nodes which have yet to be reached	
		if(	nodeVisit[k] == False):
			# This is not the best since not all nodes have been checked!
			couldBeBest = False
			
			# This is where I catch if the the graph is not connected which
			# makes the problem impossible to solve. So return -1.00 and quit
			if( adjMatrix[curNode][k] == "inif"):
				print "-1.00"
				sys.exit(0)
			
			# Calculates the Expected Value
			tempEv = float( curEv +( adjMatrix[curNode][k] * curProb ) )
			# But this means that this current path COULD be best time once it
			# reach every point
			if ( tempEv < bestEvTime or bestEvTime == -1):
				findEv( k, curProb, tempEv)
			

	# Checks if we have found a new best time or if best time hasnt been set 
	if couldBeBest and (curEv < bestEvTime or bestEvTime == -1):
		bestEvTime = curEv
	
		 
	# Must set to not visited since we have already check this sub problem now must
	# recurse out and try another path
	nodeVisit[curNode] = False

# Call my function to get the best expected value
findEv(0,1,float(0))

# round answer to 2 decimal places and print it out
print "%.2f" % bestEvTime

