# Lab 1 - Git Fundamentals
Exercising Git fundamentals discussed during the first lecture. You must have created a GitHub account in order to take part in this exercise.

1. Log in to GitHub and Create a public repository in the SSU-370 organization with the name 
**yourLastNameyourFirstName-Lab1**.
2. Once the repository has been created, click on the **Settings** tab.
3. On the *Settings* screen, click on the **Collaborators** option in the left hand navigation bar.
4. In the **Collaborators** interface, add **fisher-CS370** as a collaborator with write access.
5. Click on the **Code** tab.
6. On the **Code** page, click the **Clone or Download** button.
7. In the cloning dialog, select the **Use HTTPS** option.
8. Copy the URL provided.
9. Open a local terminal session on your workstation (do not connect to your student account on Blue).
10. Using the terminal, change your working directory to the Desktop.
11. Using the terminal, make a new directory named **Lab1**.
12. Using the terminal, change your working directory to **Lab1**.
13. Using the terminal and the URL for your repository, run the command **git clone {URL}**. You will be prompted for your Git credentials.
14. Once your repository has been cloned, using the terminal, change your working directory to the newly created directory with the same name as your repository. 
15. Using the terminal, run the command **git branch**. Note that there should only be one branch listed: master. Note the indicator that this is your active branch.
16. In your repository directory, create a new, empty text file. You can name it whatever you like.
17. Using the terminal, run the command **git commit -m "first commit"**. Note that there is nothing to commit.
18. In the terminal, run the command **git add .** to add your changes to the stage for tracking. Run the commit command again. Your changes are now tracked in your local branch.
19. In the terminal, run the command **git push -u origin master**. This will push your changes up to the remote repo.
20. In the terminal create a new branch in your repository using the command **git checkout -b Branch1**. Run the command **git branch** again. Note that your newly created branch appears and that it is now your active branch.
21. Open the empty text file created in step 16. Add the text, *'Hello, CS370'* to the file. Save the file. 
22. In the terminal, run the add, commit and push commands again.  For your commit message, use *"added text to Branch1"*. **REMEMBER THAT WHEN YOU PUSH, YOU MUST TARGET "origin {branch-name}" NOT "origin master"**.
23. If you are interested, you may switch between the **master** branch and **Branch1** using **git checkout** and can open your text file in each branch to observe that they are in fact different.
24. Log into GitHub again. Navigate to your repository. 
25. On the **Code** tab, click on the **Branch** drop down (it should currently be set to **master**). Select your **Branch1**.
26. Click the **New pull request** button. A **Compare changes** form should appear. Note that there is a dialog comparing **Branch1** to **master**. Scrolling down, you should see the changes that you made to your file on **Branch1**. There should be no merge conflicts (a line next to your comparison should say **Able to merge**).
27. In the **Write** dialog area, add a message saying **@fisher-CS370 please review**.
28. Click on the **Create pull request** button at the bottom of the dialog. This will notify me that I need to review your PR. Once I have merged your PR, the lab is complete.
