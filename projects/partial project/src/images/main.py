import imageio
import numpy as np

def imgToCSVArray(nombreArchivo, binary=False):
  im = imageio.imread(f"""{nombreArchivo}.png""",pilmode='L')

  array1 = np.asarray(im)

  if binary:
    array1 = np.where(array1<250, 1, array1)
    array1 = np.where(array1>=250, 0, array1)


  np.savetxt(f"""{nombreArchivo}.csv""", array1, delimiter=",",fmt='%i')


def CSVArrayToIMG(nombreArchivo,binary=False):
  array1 = np.genfromtxt(f"""{nombreArchivo}.csv""",delimiter=',',dtype=None)
  
  if binary:
    array1 = np.where(array1==0, 255, array1)
    array1 = np.where(array1==1, 0, array1)

  array1 = array1.astype(np.uint8)

  imageio.imwrite(f"""{nombreArchivo}Result.png""", array1)


#CSVArrayToIMG("caballoSSM")
#CSVArrayToIMG("camelloCDT")
#imgToCSVArray("caballoM")
# CSVArrayToIMG("caballoCDT")
# CSVArrayToIMG("caballoEDT")
# CSVArrayToIMG("caballoMDT")

CSVArrayToIMG("caballoSkeleton")
#CSVArrayToIMG("nubePuntosCaballo")