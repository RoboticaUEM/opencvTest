#importing the module cv2 and numpy
import cv2
import numpy as np

def map_range(x, in_min, in_max, out_min, out_max):
	return (x - in_min) * (out_max - out_min) // (in_max - in_min) + out_min

#imagergb = cv2.imread('mesa.png')
cap = cv2.VideoCapture('mesa.m4v')
if not cap.isOpened():
    print("Cannot open camera")
    exit()

ret, imagergb = cap.read()
if not ret:
	print("Can't receive frame (stream end?). Exiting ...")
	exit()

esq0 = [535 , 143]
esq1 = [879 , 121]
esq2 = [1278 , 520]
esq3 = [2 , 568]

#alto = imagergb.shape[0]
#ancho = imagergb.shape[1]
print(imagergb.shape)

alto = 900
ancho = 650

roiOutTL = [50, 50]	
roiOutBR = [600, 800]

srcpts =  np.float32([esq0, esq1, esq2, esq3])
destpts = np.float32([esq0, esq1, esq2, esq3])

cv2.imshow('frame', imagergb)
cv2.waitKey(10)
rango = 100
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
	resultimage = cv2.warpPerspective(imagergb, resmatrix, (ancho, alto))

	cv2.imshow('frame', resultimage)
	cv2.waitKey(50)

print("Video...")
cv2.waitKey(500)

while True:
	ret, imagergb = cap.read()
	if not ret:
		print("Can't receive frame (stream end?). Exiting ...")
		break

	resultimage = cv2.warpPerspective(imagergb, resmatrix, (ancho, alto))

	cv2.imshow('frame', resultimage)
	if cv2.waitKey(50) == ord('q'):
		break

print("Pulse tecla para terminar: ")
cv2.waitKey(0)

cap.release()
cv2.destroyAllWindows()

