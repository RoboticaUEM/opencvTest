#importing the module cv2 and numpy
import cv2
import numpy as np

def map_range(x, in_min, in_max, out_min, out_max):
  return (x - in_min) * (out_max - out_min) // (in_max - in_min) + out_min

#while True:
#reading the image which is to be transformed
imagergb = cv2.imread('out.jpg')
#specifying the points in the source image which is to be transformed to the corresponding points in the destination image
#srcpts = np.float32([[53,767],[229,674],[399,578],[489,528],[538,486],[597,469],[633,522],[766,628],[1072,860]])
#destpts = np.float32([[200,715],[200,572],[200,426],[200,349],[200,285],[750,259],[750,340],[750,502],[750,857]])
#srcpts = np.float32([[53,767],[489,528],[633,522],[1072,860]])
#destpts = np.float32([[200,715],[200,349],[750,340],[750,857]])
srcpts = np.float32([[53,767],[489,528],[633,522],[1072,860]])
destpts = np.float32([[53,767],[53,528],[1072,522],[1072,860]])

for i in range(100):
        

#applying PerspectiveTransform() function to transform the perspective of the given source image to the corresponding points in the destination image
resmatrix = cv2.getPerspectiveTransform(srcpts, destpts)
#applying warpPerspective() function to display the transformed image
resultimage = cv2.warpPerspective(imagergb, resmatrix, (1300, 865))
c='a'
while c != 27:
	#displaying the original image and the transformed image as the output on the screen
	cv2.imshow('frame', imagergb)
	cv2.waitKey(0)
	cv2.imshow('frame', resultimage)
	c = cv2.waitKey(0)

