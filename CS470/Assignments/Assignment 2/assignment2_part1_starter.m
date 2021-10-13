% Vince Bjazevic
%UNCOMMENT this line BEFORE SUBMISSION
function assignment2_part1_starter(id) %Argument id represents the image number to be reconstructed
%Download the ORL face database from http://www.cl.cam.ac.uk/Research/DTG/attarchive/pub/data/att_faces.zip.
clear;

N = 40*5; %Total images = First five images from each of the 40 face directories s1 .. s40
d = 112*92; %They all have same size
A = zeros(d,N); %Store all the images column wise in A (like the matrix X in the worksheet)

count = 0;
for i=1:40
    for j=1:5 
        fname = sprintf ('att_faces/s%d/%d.pgm',i,j);
        im = im2double(imread(fname));   
        count = count+1;
        %TODO 1: Store each of the 200 images in a column of matrix A. You
        %should use the variable count to represent the column index
        A(:,count) = im(:);

    end
end

%Before computing the covariance matrix, we need to subtract the mean of all images from each column of matrix A
%TODO 2: First Compute mean
meanA = mean(A, 2); %Look into matlab function mean to compute this. meanA should be a matrix of size d x 1

%TODO 3: Now subtract meanA from each column of A.
B = repmat(meanA,1,N);
A =  minus(A,B);%One fast way to so this is to replicate meanA N times using repmat and then subtract from A. See matlab function repmat

%Compute the matrix L = A'A (where A' is the transpose of matrix A). This
%is a matrix of size N x N
L = A'*A;

[V,D] = eig(L); %Computes eigenvectors in matrix V and eigenvalues in matrix D

%Right now we have obtained eigenvectors for matrix L but we need eigenvectors for original covariance matrix C = A*A'
%Recall, if v is an eigvec of L, then Av is an eigvec of C with the same eigenvalue
%Update V.
V =  A*V;
% Multiplying v by Av destroys its unit-normality property, so we divide it
% by its magnitude as below
for i=1:N 
    V(:,i) = V(:,i)/norm(V(:,i)); 
end 

% Size of V is d X N. That is total of N eigenvectors, each of size d x 1 stored column wise.
% Matlab stores eigenvectors in increasing order of eigenvalues. To make it convenient to take
% first k eigenvectors, we will reverse the order of the columns of V
V = V(:,end:-1:1); 
D = diag(D); 
D = D(end:-1:1);

% TODO 4: Compute eigencoefficients: This is multiplication of transpose of matrix V with matrix A. It is a matrix of size N x N  
eigcoeffs = V' * A;

%Let us reconstruct a specific face image for different values of k
%COMMENT this line BEFORE SUBMISSION
%id = 100; %Variable representing the image to be reconstructed; in this case reconstructing 100th face.
for k = [2 10 20 50 75 100 125 150 175 200]
    %TODO 5: Store the top k eigenvectors. This would be the first k columns of V
    topk_V = V(:,1:k);
    %TODO 6: Store the eigencoefficients of the id^th image. It is the id^th column of eigcoeffs (computed under TODO: 4)
    eig_id = eigcoeffs(:,id);
    %TODO 7: Get the first k coefficients of eig_id
    eig_id_k = eig_id(1:k);
    
    %We have the top k eigenvectors in topk_V (matrix of size d x k) and k eigencoefficients in eig_id_k (matrix of size k x 1).
    %TODO 8: Use topk_V and eig_id_k to get the reconstructed image (of size d x 1). See lecture notes to obtain the formula
    recons = topk_V * eig_id_k;
    recons = recons + meanA;
    
    %TODO 9: recons is currently of size (d x 1). Reshape it back to 112 x 92 image
    recons = reshape(recons,112,92);
    imshow (recons, []); 
    title(sprintf('k=%d',k));
    pause; %Pressing space bar will show the next reconstructed image
end

%Display the top 25 eigenfaces
for i=1:25
    
    %TODO 10: Obtain i^th eigenface from matrix V. Store it in variable eigFace. It is of size d x 1
    eigFace = V(:,i);
    
    %TODO 11: Reshape the column vector into matrix of size 112 x 92. 
    eigFace = reshape(eigFace,[112,92]); 
    
    %Plot each eigenface in one figure using subplot
    figure(3); subplot(5,5,i); imshow(eigFace, []);   
end
