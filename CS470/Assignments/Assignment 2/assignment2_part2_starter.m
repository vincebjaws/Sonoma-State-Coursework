clear;
% Vince Bjazevic
N = 40*5; %Number of training images.
Ntest = 40*5; %Number of test images
d = 112*92;
A = zeros(d,N); %Store all the training images column wise in A
id = zeros(N,1); %Array storing the label (identity) of each training image
count = 0;

%Load the training images (First five images for each of 40 persons)
for i=1:40
    for j=1:5
        fname = sprintf ('att_faces/s%d/%d.pgm',i,j);
        im = double(imread(fname));   
        count = count+1;
        
        %TODO 1 (same as part 1): Store each of the training images in a column of matrix A.
        A(:,count) = im(:);
        
        %TODO 2: Record the label of the person in array id 
        id(count) = i;
        
    end
end

%TODO 3: Perform the same steps as in part 1 to compute the eigencoefficients for
%the training images. These will be several lines of code taken from part 1.
meanA = mean(A,2);
A = minus(A, meanA);
L = A' *A;
[V,D] = eig(L);
V= A*V;


for i=1:N
    V(:,i) =  V(:,i)/norm(V(:,i));
end


V = V(:,end:-1:1);
D = diag(D);
D = D(end:-1:1);

eigcoeffs_training = V' * A; % This will be a matrix of size N x N 

%Test recognition rate for different values of k (max value is N-1)
for k = [1 2 3 5 10 20 30 40 50 60 75 100 125 150 160 170 180 185 190 195 199]
    rec_rate = 0; %Variable that stores recognition rate of test images
    %Load test images and predict their identity.
    for i=1:40
        for j=6:10
            fname = sprintf ('att_faces/s%d/%d.pgm',i,j); %Format filename of the test image
            im = double(imread(fname));
            %TODO 4: Compute top-k eigencoefficients of this test image. 
            %This will be based on matrix V as well as meanA that were computed in the *training phase*
            test_image =im(:);
            
            test_diff = test_image - meanA;  
 
            eigcoeffs_test = V'*test_diff;
            %TODO 5: Figure out the *index* of the closest eigen-coefficient from among the top-k coefficients in array *eigcoeffs_training*
            diff = eigcoeffs_test(1:k,:) - eigcoeffs_training(1:k,:);

            
            sum_of_diff = sum(diff.^2, 1);
            [Val, index] = min(sum_of_diff);
            
            %TODO 6: Based on the index, compute the predicted label.
            predicted_label = id(index);
            
            %TODO 7: If the prediction matches the actual label, increment the recognition rate rec_rate
            if predicted_label == i
                rec_rate = rec_rate + 1;
            end
        end
    end
    rec_rate = rec_rate/Ntest;
    fprintf ('\nFor k= %d, Rec rate = %f',k,100*rec_rate);
end
