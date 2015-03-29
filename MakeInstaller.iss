;InnoSetup installer-builder script for OpenGLCellViewer.
;V.Heinitz, 2015-03-29


[Setup]
AppName=OpenGLCellViewer
AppVerName=OpenGLCellViewer_0.2
OutputBaseFilename=OpenGLCellViewer_0.2
AppPublisher=vheinitz
AppPublisherURL=http://heinitz-it.de
AppSupportURL=http://heinitz-it.de
AppUpdatesURL=http://heinitz-it.de
AppCopyright=Copyright © 2015 Valentin Heinitz
DefaultDirName={pf}\\vheinitz\\OpenGLCellViewer
DefaultGroupName=vheinitz\OpenGLCellViewer
DisableDirPage=no
DisableProgramGroupPage=yes
AllowNoIcons=yes
OutputDir=bin\
BackColor=clBlue
;SetupIconFile=..\OpenGLCellViewer\app.ico
Compression=lzma
;WizardImageFile=.\res\OpenGLCellViewerSetup.bmp
;WizardSmallImageFile=.\res\OpenGLCellViewerSetup_s.bmp
SolidCompression=yes


[Languages]
Name: "en"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "c:\Qt\4.8.4\bin\QtCore4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "c:\Qt\4.8.4\bin\QtGui4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "c:\Qt\4.8.4\bin\QtOpenGL4.dll"; DestDir: "{app}"; Flags: ignoreversion

Source: "release\OpenGLCellViewer.exe"; DestDir: "{app}"; Flags: ignoreversion



[Icons]
Name: "{group}\OpenGLCellViewer"; Filename: "{app}\OpenGLCellViewer.exe"
Name: "{group}\{cm:UninstallProgram,OpenGLCellViewer}"; Filename: "{uninstallexe}"
Name: "{userdesktop}\OpenGLCellViewer"; Filename: "{app}\OpenGLCellViewer.exe"; Tasks: desktopicon
