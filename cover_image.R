mdl <- pdmphmc::build("cover_image.cpp")
ctrl <- pdmphmc::pdmphmc_control()
ctrl$lambda <- c(1,10,0)
fit <- pdmphmc::run(mdl,Tmax=100,warmupFrac = 0.0,samples=100000L,
                    chains=1L,fixedMiDiag = list(x=c(1,1)))



mdl.r <- pdmphmc::build("cover_image.cpp",process.type = "RM")




fit.r <- pdmphmc::run(mdl.r,Tmax=100,warmupFrac = 0.0,samples=100000L,chains=1L,
                      control = ctrl,fixedMiDiag = list(x=c(1,1)),seed=123)

pdf("cover_image.pdf",height = 14,width=7)
par(mfrow=c(2,1),mai = c(1, 0.1, 0.1, 0.1))

ngx <- 256L
ngy <- 512L
xg <- seq(from=-2,to=2,length.out=ngx)
yg <- seq(from=-0.6,to=4.5,length.out=ngy)

dens <- matrix(0.0,ngx,ngy)
for(i in 1:ngx) for(j in 1:ngy) dens[i,j] <- dnorm(xg[i])*dnorm(yg[j],mean=xg[i]^2,sd=0.2)

image(x=xg,y=yg,z=dens,
      col=gray.colors(32,start=0.2,end=1.0, rev=TRUE),
      axes=FALSE,
      xlab="",
      ylab="",useRaster = TRUE )
sam <- fit@pointSamples[,,1:2]
lines(sam[,1],sam[,2],col="red",lwd=0.2)

image(x=xg,y=yg,z=dens,col=gray.colors(32,start=0.2,end=1.0, rev=TRUE),
      axes=FALSE,
      xlab="",
      ylab="",
      useRaster = TRUE)
r.sam <- fit.r@pointSamples[,,1:2]
lines(r.sam[,1],r.sam[,2],col="red",lwd=0.2)
dev.off()
