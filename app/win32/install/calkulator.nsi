#
# setup script for nullsoft installer
#
# calculator.net
# (c) 2003 andrzej lichnerowicz. all rights reserved.
#
# for conditions of distribution and use, see copyright 
# notice in licence.txt
#
# Changeslog:
# 23 Mar 2003	AL	+ initial revision
#

!define MUI_PRODUCT "Calkulator"
!define MUI_VERSION "1.2.1"
!include "MUI.nsh"

!packhdr tmp.dat "upx --best tmp.dat"

SetCompressor bzip2
SetDateSave on
SetDatablockOptimize on
CRCCheck on
SilentInstall normal
ShowInstDetails show

InstType "Normal"
InstType "Lite"

OutFile "Calkulator121.exe"
InstallDir "$PROGRAMFILES\${MUI_PRODUCT}"

!define MUI_WELCOMEPAGE
!define MUI_LICENSEPAGE
!define MUI_COMPONENTSPAGE
!define MUI_DIRECTORYPAGE
!define MUI_FINISHPAGE
  
!define MUI_ABORTWARNING

!define MUI_UNINSTALLER
!define MUI_UNCONFIRMPAGE

!define MUI_ICON "${NSISDIR}\Contrib\Icons\adni18-installer-B.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Icons\adni18-uninstall-C.ico"
!define MUI_UI "${NSISDIR}\Contrib\UIs\modern2.exe"
!insertmacro MUI_SYSTEM
!insertmacro MUI_LANGUAGE "English"

LangString AppDesc ${LANG_ENGLISH} "Install Calkulator application."
LangString AppCoreDesc ${LANG_ENGLISH} "Install main Calkulator application files."
LangString StartDesc ${LANG_ENGLISH} "Create Start Menu shortcuts."
LangString DeskDesc ${LANG_ENGLISH} "Create Desktop shortcut."
LangString QuickDesc ${LANG_ENGLISH} "Create Quicklaunch shortcut."

LicenseData "..\Licence.txt"

!insertmacro MUI_RESERVEFILE_WELCOMEFINISHPAGE

SubSection "Application" App

Section "Core" AppCore
    SectionIn 1 2 RO
    SetOutPath "$INSTDIR"
    File "..\bin\Calk.exe"
    File "..\bin\CalCore.dll"
    File "..\bin\Readme.txt"

    WriteRegStr HKLM "SOFTWARE\Exodus\Calkulator" "Path" "$INSTDIR\"
SectionEnd

Section "Start Menu shortcuts" Start
    SectionIn 1 2
    CreateDirectory $SMPROGRAMS\Calkulator
    CreateShortCut "$SMPROGRAMS\Calkulator\Calkulator.lnk" "$INSTDIR\Calk.exe" ""
    CreateShortCut "$SMPROGRAMS\Calkulator\Readme.lnk" "$INSTDIR\Readme.txt" ""
    CreateShortCut "$SMPROGRAMS\Calkulator\Uninstall.lnk" "$INSTDIR\uninst-calc.exe" ""
SectionEnd

Section "Desktop shortcut" Desk
    SectionIn 1 
    CreateShortCut "$DESKTOP\Calkulator.lnk" "$INSTDIR\Calk.exe" ""
SectionEnd

Section "Quicklaunch shortcut" Quick
    SectionIn 1 
    CreateShortCut "$QUICKLAUNCH\Calkulator.lnk" "$INSTDIR\Calk.exe" ""
SectionEnd

SubSectionEnd

Section -post
    WriteUninstaller "$INSTDIR\uninst-calc.exe"
SectionEnd


!insertmacro MUI_FUNCTIONS_DESCRIPTION_BEGIN
    !insertmacro MUI_DESCRIPTION_TEXT ${App} $(AppDesc)
    !insertmacro MUI_DESCRIPTION_TEXT ${AppCore} $(AppCoreDesc)
    !insertmacro MUI_DESCRIPTION_TEXT ${Start} $(StartDesc)
    !insertmacro MUI_DESCRIPTION_TEXT ${Desk} $(DeskDesc)
    !insertmacro MUI_DESCRIPTION_TEXT ${Quick} $(QuickDesc)
!insertmacro MUI_FUNCTIONS_DESCRIPTION_END

Section "Uninstall"
    Delete "$INSTDIR\Calk.exe"
    Delete "$INSTDIR\CalCore.dll"
    Delete "$INSTDIR\Readme.txt"

    Delete "$INSTDIR\Uninstall.exe"

    RMDir "$INSTDIR"

    Delete "$QUICKLAUNCH\Calkulator.lnk"
    Delete "$DESKTOP\Calkulator.lnk"

    Delete "$SMPROGRAMS\Calkulator\Calkulator.lnk"
    Delete "$SMPROGRAMS\Calkulator\Readme.lnk"
    Delete "$SMPROGRAMS\Calkulator\Uninstall.lnk"
    RMDir "$SMPROGRAMS\Calkulator"
    
    DeleteRegKey HKLM "SOFTWARE\Exodus\Calkulator"

    !insertmacro MUI_UNFINISHHEADER
SectionEnd



