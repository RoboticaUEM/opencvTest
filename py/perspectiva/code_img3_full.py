#importing the module cv2 and numpy
import cv2
import numpy as np

def map_range(x, in_min, in_max, out_min, out_max):
	return (x - in_min) * (out_max - out_min) // (in_max - in_min) + out_min

#while True:
imagergb = cv2.imread('img3_out.jpg')

# Esquinas del ROI
esq0 = [290 , 70]	#top-left
esq1 = [696 , 42]	#top-right
esq2 = [684 , 779]	#buton-right
esq3 = [289 , 720]	#buton-left
tamImgOut = [600, 800]

srcpts =  np.float32([esq0, esq1, esq2, esq3])
destpts = np.float32([esq0, esq1, esq2, esq3])

print(destpts)
cv2.imshow('frame', imagergb)
cv2.waitKey(0)
rango = 30
for i in range(rango+1):
	destpts[0,0] = map_range(i, 0, rango, esq0[0], 0)
	destpts[0,1] = map_range(i, 0, rango, esq0[1], 0)
	destpts[1,0] = map_range(i, 0, rango, esq1[0], tamImgOut[0])
	destpts[1,1] = map_range(i, 0, rango, esq1[1], 0)
	destpts[2,0] = map_range(i, 0, rango, esq2[0], tamImgOut[0])
	destpts[2,1] = map_range(i, 0, rango, esq2[1], tamImgOut[1])
	destpts[3,0] = map_range(i, 0, rango, esq3[0], 0)
	destpts[3,1] = map_range(i, 0, rango, esq3[1], tamImgOut[1])
	print(i)
	print(destpts)

	resmatrix = cv2.getPerspectiveTransform(srcpts, destpts)
	resultimage = cv2.warpPerspective(imagergb, resmatrix, (tamImgOut[0], tamImgOut[1]))

	cv2.imshow('frame', resultimage)
	cv2.waitKey(0)

