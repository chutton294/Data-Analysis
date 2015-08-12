#workflow to demonstrate calculation of hydrologic signatures

setwd("C:/Users/....")

source("signatures.R")

#read data from file
data <- read.table("exampleData.txt", header = TRUE)

#see source Signatures.R for further information of how the signatures are calculated

####binary vector indicated whether or not the signature value should be calculate. Useful in optimisation if not used
used <- rep(1,9) 

#####calculate signatures 
sigs <- calcAllSigs(data$Q,data$P, used)

print(paste("Runoff Coefficient: ", sigs[1]))
print(paste("Variance Ratio: ", sigs[2]))
print(paste("Rising Limb Density: ", sigs[3]))
print(paste("Falling Limb Density: ", sigs[4]))
print(paste("Slope Flow Duration Curve: ", sigs[5]))
print(paste("Slope Peak Distribution: ", sigs[6]))
print(paste("Base FLow Index: ", sigs[7]))
print(paste("High Pulse Count: ", sigs[8]))
print(paste("Q90/Q50: ", sigs[9]))
