cd /d "D:\work\LostStory\LostStory" &msbuild "LostStory.vcxproj" /t:sdvViewer /p:configuration="Debug" /p:platform="Win32" /p:SolutionDir="D:\work\LostStory" 
exit %errorlevel% 