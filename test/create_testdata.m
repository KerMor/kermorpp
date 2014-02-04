k = kernels.KernelExpansion;

nc = randi(200);
xdim = randi(200);
fdim = randi(200);

k.Centers.xi = rand(xdim, nc) * 10;
k.Ma = (rand(fdim, nc)-.5) * 20;

% Gaussian
k.Kernel = kernels.GaussKernel(xdim + rand(1)*10);
dir = fullfile('test','gaussian');
k.exportToDirectory(dir);
x = rand(xdim,randi(200));
Util.saveRealMatrix(x,'points.bin',dir);
fx = k.evaluate(x);
Util.saveRealMatrix(fx,'eval.bin',dir);

% Wendland
ke = kernels.Wendland;
ke.Gamma = xdim + rand(1)*10;
ke.d = xdim;
ke.k = 3;
k.Kernel = ke;
dir = fullfile('test','wendland');
k.exportToDirectory(dir);
x = rand(xdim,randi(200));
Util.saveRealMatrix(x,'points.bin',dir);
Util.saveRealMatrix(k.evaluate(x),'eval.bin',dir);