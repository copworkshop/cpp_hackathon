# Github Copilot Hackathon - C++

## Use Case: 

Your team was assigned to maintain a legacy application, written and forgotten long time ago. The application helps florist shop to maintain their stock, control prices and define policies of how the value of the stock changes over time.
You were told that application was poorly maintained, so you were given some time to make yourself comfortable with it. The plan is to modernize it and expand its functionalities, so make sure you spend the initial preparation time effectively.


## Pre-requisite:

### Environment preparation:
1.	Log-in to your lab virtual machine using credentials provided.
2.	Run PowerShell as Administrator.
3.  Enable WSL2 and install Ubuntu machine. [Instructions](https://docs.microsoft.com/en-us/windows/wsl/install). 
    TL;DR:
    ```powershell

    dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart

    dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart

    wsl --install -d Ubuntu

    shutdown /r /t 0
    ```
    Wait for the machine to restart.

```
IMPORTANT: From now on:
* all actions on github account shall be done using github credentials associated with lab 
  (the same credentials you will use to sign in to CoPilot in later steps)
* Unless explicitly stated, all setup commands shall be executed via WSL bash terminal.
```
    
5.	Generate ssh key and add it to Github account associated to the lab. [Instructions](https://docs.github.com/en/github/authenticating-to-github/connecting-to-github-with-ssh)
6.  Clone hackathon repository to your wsl environment using ssh:
    ```
    git clone git@github.com:copworkshop/cpp_hackathon.git
    cd cpp_hackathon
    ```
7.  Run `sudo ./bootstrap.sh` script to install necessary tools and dependencies.
    ```
    NOTE: You may need to run `chmod +x *.sh` to make scripts executable.
    ```

8.  Activate Python Virtual Env using `source venv/bin/activate` command.
    ```
    NOTE: You must activate the virtual environment each time you open a new terminal.
    ```
9.  Run `./prepare.sh` script to prepare necessary conan packages.

#### If you are using VSCode (Recomended approach):
9. Open repository in VSCode from WSL. 
    ``` 
    code .
    ```
10. Set up IDE (VSCode preferred) to work with WSL environment. [Instructions](https://code.visualstudio.com/docs/cpp/config-wsl)
    TL;DR:
    ```
    1. Install Remote - WSL extension in VSCode.
    2. Open WSL terminal in VSCode.
    3. Install C++ extension in WSL environment.
    4. Open CMake project in WSL environment.
    ```
11. Install CoPilot extension in VSCode. [Instructions](https://marketplace.visualstudio.com/items?itemName=GitHub.copilot)
    TL;DR:
    ```
    1. Install CoPilot extension in VSCode.
    2. Sign-in to your lab Github account.
    ```
#### Alternative: If you are not using VSCode:
9.  Use `./build.sh` or direct cmake commands to build and run tests.
10. Configure your IDE to use CoPilot.


## Workflow:

### Working on this repository:
1. Use `./build.sh` script to build and run tests for local verification.

OR

2. Use VSCode `Ctrl+Shift+B` to build and run tests.


### Working on challenges:
1. Use branch with name *team/*<your_team_name> as your trunk.
2. Associated Github Action should reflect your progess:
    a. On initial run, it may fail due to unit test coverage threshold set:

            
            - name: Generate a code coverage report
              (...)
                  fail-under-line: 75%
    As you progress, the pipeline should become green.
3. Make sure that your Github Actions workflows reflect your progress - add, them, modify them, store necessary artifacts as a proof of progress.


## Challenges:

#### 1.	High level overview and documentation
    a.	Problem: 
    You already see that the previous team did not leave any documentation behind them. Make sure you understand on a high level what the application does, and you have appropriate code documentation available.
    b.	Success Criteria:
    You are able to automatically publish Github pages using Github actions that will consist of high-level documentation of the application, automatically generated documentation (sphinx? Doxygen?). 
#### 2.	Unit Testing
    a.	Problem: 
    Once you understand how the application works, it would be good to see it works. Make sure you have proper code coverage.
    b.	Success Criteria:
    i.	You are able to compile and run unit tests both locally and through Github actions. 
    ii.	You are able to measure code coverage and report it through Github actions. Pick reasonable code coverage benchmark and fail builds if coverage goes below that (we suggest 75%)
#### 3.	Refactoring
    a.	Problem:
    You have already noticed that some parts of the current application are too complicated. Since the code will be here for a while, you decide that it is a good moment for refactoring.
    b.	Success Criteria:
    You are able to measure cyclomatic complexity of the application through github actions. You have refactored the most complex parts of the system without regression and dropped the complexity to an acceptable number.
#### 4.	Database connection
    a.	Problem:
    Currently the application uses files to store data. You want to migrate the application to use the cloud database.
    b.	Success Criteria:
        i.	Application reads db configuration from a configuration file
        ii.	Application can either use file (start with an argument /infile <filename>) or database (start with an argument /db  <db_configuration.filename>)
        iii. Application kept an ability to produce an output file in json form (invoked argument /outfile filename). If an application was started with /db parameter and /outfile parameters, it outputs both to database and to a file.
        iv.	Application can read and store data in the database
        v.	Application connects to the database securely and with authentication

#### 5.	REST API
    a.	Problem:
    Current app must be run manually at the end of business day, so that the information is updated appropriately. The customer wants to integrate the business logic with external services through API so that both reads and updates can be performed on demand. 
    b.	Success Criteria:
        i.	You have set up an HTTP server that will be able to serve appropriate endpoints:
            *	/stock – Outputs existing stock data in JSON format
            *	/update (POST) – performs an update action of the current stock
        ii.	You have integrated the existing application with the webserver 
        Note: The preferred approach would be to set up a webserver in a language, that can use the C++ modules directly. We strongly suggest Python for server and direct calls to business logic of what you initially saw as an UpdateQuality() method.
        iii. You have covered the solution with unit tests

