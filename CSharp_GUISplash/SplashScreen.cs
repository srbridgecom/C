/*C#, GUI, add a splash screen to project

Category: C#

Written by Ryan Bridglal

File Original Date September 23rd, 2008.


A quick and easy way to get a fast splash screen within your C# projects is to add:

 

#1. a new form to your project and call it splashscreen.cs

 

#2. Enter the following code to your main form:  */

private void Form1_Load(object sender, EventArgs e)

{

 

// Display the splash screen

splashscreen SplashScreen = new splashscreen();

SplashScreen.Show();

 

// show the splash form and update text as events occur

SplashScreen.Text = "Some info...";

SplashScreen.Refresh();

// call the method to perform the action


// Repeat the update of the text and calling methods until program is ready to run.

 

// Close the splash screen

SplashScreen.Close();

 

}
