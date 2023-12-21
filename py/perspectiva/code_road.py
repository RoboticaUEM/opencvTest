#importing the module cv2 and numpy
import cv2
import numpy as np

def map_range(x, in_min, in_max, out_min, out_max):
	return (x - in_min) * (out_max - out_min) // (in_max - in_min) + out_min

imagergb = cv2.imread('road.jpg')

esq0 = [364, 182]
esq1 = [397, 182]
esq2 = [736, 823]
esq3 = [34, 823]

height = imagergb.shape[0]
width = imagergb.shape[1]
print(imagergb.shape)

# (237, 200), (600, 200), (600, 823), (237, 823)
roiOutTL = [237, 300]	
roiOutBR = [600, 823]

srcpts =  np.float32([esq0, esq1, esq2, esq3])
destpts = np.float32([esq0, esq1, esq2, esq3])

cv2.imshow('frame', imagergb)
cv2.waitKey(0)
rango = 30
for i in range(rango+1):
	destpts[0,0] = map_range(i, 0, rango, esq0[0], roiOutTL[0])
	destpts[0,1] = map_range(i, 0, rango, esq0[1], roiOutTL[1])
	destpts[1,0] = map_range(i, 0, rango, esq1[0], roiOutBR[0])
	destpts[1,1] = map_range(i, 0, rango, esq1[1], roiOutTL[1])
	destpts[2,0] = map_range(i, 0, rango, esq2[0], roiOutBR[0])
	destpts[2,1] = map_range(i, 0, rango, esq2[1], roiOutBR[1])
	destpts[3,0] = map_range(i, 0, rango, esq3[0], roiOutTL[0])
	destpts[3,1] = map_range(i, 0, rango, esq3[1], roiOutBR[1])

	resmatrix = cv2.getPerspectiveTransform(srcpts, destpts)
	resultimage = cv2.warpPerspective(imagergb, resmatrix, (width, height))

	cv2.imshow('frame', resultimage)
	cv2.waitKey(0)

print("Pulse tecla para terminar: ")
cv2.waitKey(0)
cv2.destroyAllWindows()

