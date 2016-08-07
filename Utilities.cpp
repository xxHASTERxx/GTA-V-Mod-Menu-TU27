#include "stdafx.h"

#define APPSZ_XAM                       ("xam.dll")
#define APPSZ_UVBASE                    ("uvbase.xex")
#define APPSZ_XLIVEBASE                 ("xlivebase.xex")
#define APPSZ_XGI                       ("xgi.xex")
#define APPSZ_SIGNINUI                  ("signin.xex")
#define APPSZ_FRIENDSUI                 ("Guide.Friends.xex")
#define APPSZ_FEEDBACKUI                ("Guide.PlayerFeedback.xex")
#define APPSZ_XMP                       ("musicplayer.xex")
#define APPSZ_GAMERPROFILE              ("gamerprofile.xex")
#define APPSZ_MARKETPLACEUI             ("marketplace.xex")
#define APPSZ_VIRTUALKEYBOARD           ("vk.xex")
#define APPSZ_QUICKCHATUI               ("Guide.ChatAndMessenger.xex")
#define APPSZ_VOICEMAILUI               ("Guide.Voicemail.xex")
#define APPSZ_ACCOUNTRECOVERY           ("Guide.AccountRecovery.xex")
#define APPSZ_CREATEPROFILE             ("createprofile.xex")
#define APPSZ_DEVICESELECTORUI          ("deviceselector.xex")
#define APPSZ_UPDATERUI                 ("updater.xex")
#define APPSZ_MINIMEDIAPLAYER           ("minimediaplayer.xex")
#define APPSZ_MESSENGER                 ("Xam.LiveMessenger.xex")
#define APPSZ_XIME                      ("ximecore.xex")
#define APPSZ_COMMUNITY                 ("Xam.Community.xex")
#define APPSZ_AVATARMINICREATOR         ("Guide.AvatarMiniCreator.xex")
#define APPSZ_WORDREGISTER              ("Xam.WordRegister.xex")
#define APPSZ_PAM                       ("pamxam.xex")
#define APPSZ_NUITROUBLESHOOTER         ("Guide.NuiTroubleshooter.xex")
#define APPSZ_NUICOMMUNITY              ("Guide.NuiCommunity.xex")
#define APPSZ_BEACONS                   ("Guide.Beacons.xex")
#define APPSZ_SOCIALPOST                ("Guide.SocialPost.xex")
#define APPSZ_FITNESS                   ("Fitness.xex")
#define APPSZ_NETWORKSTORAGESYNCUI      ("Guide.NetworkStorage.xex")
#define APPSZ_LRC                       ("xlrc.xex")


typedef PVOID                           HXAMAPP, *PHXAMAPP;

// The hardcoded handles need to remain in this order:
//  (1) UI app
//  (2) XAM
//  (3) Always running apps (order doesn't really matters)
//  (4) [In the future] other apps
#define HXAMAPP_UI                              ((HXAMAPP)0x000000FF)
#define HXAMAPP_XAM                             ((HXAMAPP)0x000000FE)
#define HXAMAPP_UVBASE                          ((HXAMAPP)0x000000FD)
#define HXAMAPP_XLIVEBASE                       ((HXAMAPP)0x000000FC)
#define HXAMAPP_XGI                             ((HXAMAPP)0x000000FB)
#define HXAMAPP_XMP                             ((HXAMAPP)0x000000FA)
#define HXAMAPP_MESSENGER                       ((HXAMAPP)0x000000F7)
#define HXAMAPP_IPTVDVR                         ((HXAMAPP)0x000000F6)
#define HXAMAPP_XIME                            ((HXAMAPP)0x000000F5)
#define HXAMAPP_COMMUNITY                       ((HXAMAPP)0x000000F4)
#define HXAMAPP_AVATARSYSCORE                   ((HXAMAPP)0x000000F3)
#define HXAMAPP_AVATARCORE                      ((HXAMAPP)0x000000F2)
#define HXAMAPP_LRC                             ((HXAMAPP)0x000000F1)

// Title HXAMAPP.  Cannot be used as the other ones, can just be used as an
// identifier.  Keep it outside of the range of the other ones and also do
// not account for it in the _HXAMAPP_Xxx_ define's below.
#define HXAMAPP_TITLE                           ((HXAMAPP)0x000000EE)

#define _HXAMAPP_MASK_                          0x0000FFFF

//
// Message Identifiers
// The high word of a message identifier is reserved
// The low word of a message identifier is a unique message number
//

#define MSGID(Area, Number)                     (DWORD)((WORD)(Area) << 16 | (WORD)(Number))
#define MSG_AREA(msgid)                         (((msgid) >> 16) & 0xFFFF)
#define MSG_NUMBER(msgid)                       ((msgid) & 0xFFFF)

//
// Message Areas
//

#define MSGAREA_NONE                            (0x0000)
#define MSGAREA_XAM                             (0x0002)
#define MSGAREA_XBASE                           MSGAREA_XAM
#define MSGAREA_SYSTEM                          (0x8000)
#define MSGAREA_XLIVEBASE                       (0x0005)
#define MSGAREA_UVBASE                          (0x0010)
#define MSGAREA_XGI                             (0x000B)
#define MSGAREA_XMP                             (0x0007)
#define MSGAREA_MSGR                            (0x0020)
#define MSGAREA_IPTV                            (0x0030)
#define MSGAREA_XIME                            (0x0040)
#define MSGAREA_LRC                             (0x0080)

//
// System Messages
//

#define XM_SYS_BASE                             MSGID(MSGAREA_SYSTEM, 0x0001)
#define XM_SYS_TITLESTARTUP                     MSGID(MSGAREA_SYSTEM, 0x0002)
#define XM_SYS_SHUTDOWN                         MSGID(MSGAREA_SYSTEM, 0x0003)
#define XM_SYS_LOAD                             MSGID(MSGAREA_SYSTEM, 0x0004)
#define XM_SYS_UNLOAD                           MSGID(MSGAREA_SYSTEM, 0x0005)
#define XM_SYS_TITLESHUTDOWN                    MSGID(MSGAREA_SYSTEM, 0x0006)
#define XM_SYS_ASYNCMESSAGE                     MSGID(MSGAREA_SYSTEM, 0x0007)
#define XM_SYS_UIINIT                           MSGID(MSGAREA_SYSTEM, 0x0008)
#define XM_SYS_PERSIST                          MSGID(MSGAREA_SYSTEM, 0x0009)
#define XM_SYS_UPDATEFRAME                      MSGID(MSGAREA_SYSTEM, 0x000A)
#define XM_SYS_THREADATTACH                     MSGID(MSGAREA_SYSTEM, 0x000B)
#define XM_SYS_THREADDETACH                     MSGID(MSGAREA_SYSTEM, 0x000C)
#define XM_SYS_LOCALECHANGE                     MSGID(MSGAREA_SYSTEM, 0x000D)
#define XM_SYS_XNOTIFYPREVIEW                   MSGID(MSGAREA_SYSTEM, 0x000E)

//
// XLiveBase
//
#define XM_LIVEBASE_LOGONDISCONNECT             MSGID(MSGAREA_XLIVEBASE, 0x8002)
#define XM_LIVEBASE_LOGONGETHR                  MSGID(MSGAREA_XLIVEBASE, 0x8003)
#define XM_LIVEBASE_LOGONGETID                  MSGID(MSGAREA_XLIVEBASE, 0x8004)
#define XM_LIVEBASE_LOGONGETUSERS               MSGID(MSGAREA_XLIVEBASE, 0x8005)
#define XM_LIVEBASE_LOGONGETNATTYPE             MSGID(MSGAREA_XLIVEBASE, 0x8006)
#define XM_LIVEBASE_LOGONCHECKUSERPRIVILEGE     MSGID(MSGAREA_XLIVEBASE, 0x8008)
#define XM_LIVEBASE_CONTENTAVAILABLE            MSGID(MSGAREA_XLIVEBASE, 0x8009)
#define XM_LIVEBASE_CONTENTUPDATEACCESSTIMES    MSGID(MSGAREA_XLIVEBASE, 0x800A)
#define XM_LIVEBASE_AREUSERSFRIENDS             MSGID(MSGAREA_XLIVEBASE, 0x800B)
#define XM_LIVEBASE_MUTELISTADD                 MSGID(MSGAREA_XLIVEBASE, 0x800C)
#define XM_LIVEBASE_MUTELISTREMOVE              MSGID(MSGAREA_XLIVEBASE, 0x800D)
#define XM_LIVEBASE_MUTELISTQUERY               MSGID(MSGAREA_XLIVEBASE, 0x800E)
#define XM_LIVEBASE_PLAYERLISTADD               MSGID(MSGAREA_XLIVEBASE, 0x800F)
#define XM_LIVEBASE_PLAYERLISTUPDATE            MSGID(MSGAREA_XLIVEBASE, 0x8010)
#define XM_LIVEBASE_PLAYERENUMERATE             MSGID(MSGAREA_XLIVEBASE, 0x8012)
#define XM_LIVEBASE_PLAYERCLOSEENUM             MSGID(MSGAREA_XLIVEBASE, 0x8013)
#define XM_LIVEBASE_PRESENCEUPDATESTATEFLAGS    MSGID(MSGAREA_XLIVEBASE, 0x8014)
#define XM_LIVEBASE_PRESENCESETGAMESESSION      MSGID(MSGAREA_XLIVEBASE, 0x8015)
#define XM_LIVEBASE_PRESENCEGETSESSION          MSGID(MSGAREA_XLIVEBASE, 0x8016)

//
// XBase
//

#define XM_BASE_SUBAREA                         MSGID(MSGAREA_XBASE, 0xF000)

#define XM_BASE_SUBAREA_CONTENT                 MSGID(MSGAREA_XBASE, 0x0000)
#define XM_BASE_CONTENTCREATE                   MSGID(MSGAREA_XBASE, 0x0001)
#define XM_BASE_CONTENTOPEN                     MSGID(MSGAREA_XBASE, 0x0002)
#define XM_BASE_CONTENTCLOSE                    MSGID(MSGAREA_XBASE, 0x0003)
#define XM_BASE_CONTENTDELETE                   MSGID(MSGAREA_XBASE, 0x0004)
#define XM_BASE_CONTENTENUMERATE                MSGID(MSGAREA_XBASE, 0x0005)
#define XM_BASE_CONTENTCREATEENUM               MSGID(MSGAREA_XBASE, 0x0006)
#define XM_BASE_CONTENTCLOSEENUM                MSGID(MSGAREA_XBASE, 0x0007)
#define XM_BASE_DEVICECREATEENUM                MSGID(MSGAREA_XBASE, 0x0008)
#define XM_BASE_DEVICECLOSEENUM                 MSGID(MSGAREA_XBASE, 0x0009)
#define XM_BASE_DEVICEENUMERATE                 MSGID(MSGAREA_XBASE, 0x000A)

#define XM_BASE_SUBAREA_UI                      MSGID(MSGAREA_XBASE, 0x1000)
#define XM_BASE_UISHOWSIGNIN                    MSGID(MSGAREA_XBASE, 0x1001)
#define XM_BASE_UISHOWFRIENDS                   MSGID(MSGAREA_XBASE, 0x1002)
#define XM_BASE_UISHOWPLAYERS                   MSGID(MSGAREA_XBASE, 0x1003)
#define XM_BASE_UISHOWMESSAGES                  MSGID(MSGAREA_XBASE, 0x1004)
#define XM_BASE_UISHOWKEYBOARD                  MSGID(MSGAREA_XBASE, 0x1005)
#define XM_BASE_UISHOWQUICKCHAT                 MSGID(MSGAREA_XBASE, 0x1006)
#define XM_BASE_UISHOWVOICEMAIL                 MSGID(MSGAREA_XBASE, 0x1007)
#define XM_BASE_UISHOWGAMERPROFILE              MSGID(MSGAREA_XBASE, 0x1008)
#define XM_BASE_UISHOWFEEDBACK                  MSGID(MSGAREA_XBASE, 0x1009)
#define XM_BASE_UISHOWMARKETPLACE               MSGID(MSGAREA_XBASE, 0x100A)
#define XM_BASE_UISHOWDEVICESELECTOR            MSGID(MSGAREA_XBASE, 0x100B)
#define XM_BASE_UISHOWUPDATER                   MSGID(MSGAREA_XBASE, 0x100C)
#define XM_BASE_UISHOWMESSAGEBOX                MSGID(MSGAREA_XBASE, 0x100D)
#define XM_BASE_UISHOWCREATEPROFILE             MSGID(MSGAREA_XBASE, 0x100E)
#define XM_BASE_UISHOWLIVEUPSELL                MSGID(MSGAREA_XBASE, 0x100F)
#define XM_BASE_UISHOWKEYBOARD_INTERNAL         MSGID(MSGAREA_XBASE, 0x1010)
#define XM_BASE_UISHOWVOICESETTINGS             MSGID(MSGAREA_XBASE, 0x1011)
#define XM_BASE_UIENABLEGUESTSIGNIN             MSGID(MSGAREA_XBASE, 0x1012)
#define XM_BASE_UISHOWPARTY                     MSGID(MSGAREA_XBASE, 0x1016)
#define XM_BASE_UISHOWCOMMUNITYSESSIONS         MSGID(MSGAREA_XBASE, 0x1017)
#define XM_BASE_UISHOWAVATARMINICREATOR         MSGID(MSGAREA_XBASE, 0x1018)
#define XM_BASE_UISHOWQUICKLAUNCH               MSGID(MSGAREA_XBASE, 0x1019)
#define XM_BASE_UISHOWWORDREGISTER              MSGID(MSGAREA_XBASE, 0x1024)
#define XM_BASE_UISHOWNUITROUBLESHOOTER         MSGID(MSGAREA_XBASE, 0x1028)
#if DBG
#endif
#define XM_BASE_UISHOWNUIGUIDE                  MSGID(MSGAREA_XBASE, 0x1030)

#define XM_BASE_SUBAREA_PROFILE                 MSGID(MSGAREA_XBASE, 0x3000)

#define XM_BASE_SUBAREA_PNG                     MSGID(MSGAREA_XBASE, 0x4000)

#define XM_BASE_SUBAREA_DOWNLOADER                  MSGID(MSGAREA_XBASE, 0X6000)
#define XM_BASE_XNUI_DELAYUI                        MSGID(MSGAREA_XBASE, 0xB001)

//
// XIME Messages
//
#define XM_XIME_INIT                            MSGID(MSGAREA_XIME, 0x0001)
#define XM_XIME_UNINIT                          MSGID(MSGAREA_XIME, 0x0002)
#define XM_XIME_SET_PROPERTY                    MSGID(MSGAREA_XIME, 0x0003)
#define XM_XIME_SET_CHARACTER                   MSGID(MSGAREA_XIME, 0x0004)
#define XM_XIME_GET_STRING                      MSGID(MSGAREA_XIME, 0x0005)

//
// Virtual key codes for XInput APIs
//

#define VK_CANCEL                       0x03
#define VK_BACK                         0x08
#define VK_TAB                          0x09
#define VK_CLEAR                        0x0C
#define VK_RETURN                       0x0D
#define VK_SHIFT                        0x10
#define VK_CONTROL                      0x11
#define VK_MENU                         0x12
#define VK_PAUSE                        0x13
#define VK_CAPITAL                      0x14
#define VK_KANA                         0x15
#define VK_HANGEUL                      0x15
#define VK_HANGUL                       0x15
#define VK_JUNJA                        0x17
#define VK_FINAL                        0x18
#define VK_HANJA                        0x19
#define VK_KANJI                        0x19
#define VK_ESCAPE                       0x1B
#define VK_CONVERT                      0x1C
#define VK_NONCONVERT                   0x1D
#define VK_ACCEPT                       0x1E
#define VK_MODECHANGE                   0x1F
#define VK_SPACE                        0x20
#define VK_PRIOR                        0x21
#define VK_NEXT                         0x22
#define VK_END                          0x23
#define VK_HOME                         0x24
#define VK_LEFT                         0x25
#define VK_UP                           0x26
#define VK_RIGHT                        0x27
#define VK_DOWN                         0x28
#define VK_SELECT                       0x29
#define VK_PRINT                        0x2A
#define VK_EXECUTE                      0x2B
#define VK_SNAPSHOT                     0x2C
#define VK_INSERT                       0x2D
#define VK_DELETE                       0x2E
#define VK_HELP                         0x2F
#define VK_0                            0x30
#define VK_1                            0x31
#define VK_2                            0x32
#define VK_3                            0x33
#define VK_4                            0x34
#define VK_5                            0x35
#define VK_6                            0x36
#define VK_7                            0x37
#define VK_8                            0x38
#define VK_9                            0x39

//
// 0x40 : unassigned
// VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
//

#define VK_APPS                         0x5D
#define VK_SLEEP                        0x5F
#define VK_NUMPAD0                      0x60
#define VK_NUMPAD1                      0x61
#define VK_NUMPAD2                      0x62
#define VK_NUMPAD3                      0x63
#define VK_NUMPAD4                      0x64
#define VK_NUMPAD5                      0x65
#define VK_NUMPAD6                      0x66
#define VK_NUMPAD7                      0x67
#define VK_NUMPAD8                      0x68
#define VK_NUMPAD9                      0x69
#define VK_MULTIPLY                     0x6A
#define VK_ADD                          0x6B
#define VK_SEPARATOR                    0x6C
#define VK_SUBTRACT                     0x6D
#define VK_DECIMAL                      0x6E
#define VK_DIVIDE                       0x6F
#define VK_F1                           0x70
#define VK_F2                           0x71
#define VK_F3                           0x72
#define VK_F4                           0x73
#define VK_F5                           0x74
#define VK_F6                           0x75
#define VK_F7                           0x76
#define VK_F8                           0x77
#define VK_F9                           0x78
#define VK_F10                          0x79
#define VK_F11                          0x7A
#define VK_F12                          0x7B
#define VK_F13                          0x7C
#define VK_F14                          0x7D
#define VK_F15                          0x7E
#define VK_F16                          0x7F
#define VK_F17                          0x80
#define VK_F18                          0x81
#define VK_F19                          0x82
#define VK_F20                          0x83
#define VK_F21                          0x84
#define VK_F22                          0x85
#define VK_F23                          0x86
#define VK_F24                          0x87
#define VK_NUMLOCK                      0x90
#define VK_SCROLL                       0x91
#define VK_OEM_NEC_EQUAL                0x92
#define VK_OEM_FJ_JISHO                 0x92
#define VK_OEM_FJ_MASSHOU               0x93
#define VK_OEM_FJ_TOUROKU               0x94
#define VK_OEM_FJ_LOYA                  0x95
#define VK_OEM_FJ_ROYA                  0x96
#define VK_LSHIFT                       0xA0
#define VK_RSHIFT                       0xA1
#define VK_LCONTROL                     0xA2
#define VK_RCONTROL                     0xA3
#define VK_LMENU                        0xA4
#define VK_RMENU                        0xA5
#define VK_BROWSER_BACK                 0xA6
#define VK_BROWSER_FORWARD              0xA7
#define VK_BROWSER_REFRESH              0xA8
#define VK_BROWSER_STOP                 0xA9
#define VK_BROWSER_SEARCH               0xAA
#define VK_BROWSER_FAVORITES            0xAB
#define VK_BROWSER_HOME                 0xAC
#define VK_VOLUME_MUTE                  0xAD
#define VK_VOLUME_DOWN                  0xAE
#define VK_VOLUME_UP                    0xAF
#define VK_MEDIA_NEXT_TRACK             0xB0
#define VK_MEDIA_PREV_TRACK             0xB1
#define VK_MEDIA_STOP                   0xB2
#define VK_MEDIA_PLAY_PAUSE             0xB3
#define VK_LAUNCH_MAIL                  0xB4
#define VK_LAUNCH_MEDIA_SELECT          0xB5
#define VK_LAUNCH_APP1                  0xB6
#define VK_LAUNCH_APP2                  0xB7
#define VK_OEM_1                        0xBA
#define VK_OEM_PLUS                     0xBB
#define VK_OEM_COMMA                    0xBC
#define VK_OEM_MINUS                    0xBD
#define VK_OEM_PERIOD                   0xBE
#define VK_OEM_2                        0xBF
#define VK_OEM_3                        0xC0
#define VK_OEM_4                        0xDB
#define VK_OEM_5                        0xDC
#define VK_OEM_6                        0xDD
#define VK_OEM_7                        0xDE
#define VK_OEM_8                        0xDF
#define VK_OEM_AX                       0xE1
#define VK_OEM_102                      0xE2
#define VK_ICO_HELP                     0xE3
#define VK_ICO_00                       0xE4
#define VK_PROCESSKEY                   0xE5
#define VK_ICO_CLEAR                    0xE6
#define VK_PACKET                       0xE7
#define VK_PLAY                         0xFA

#define VK_DVDMENU                      0x5870
#define VK_DVDANGLE                     0x5871
#define VK_DVDAUDIO                     0x5872
#define VK_DVDSUBTITLE                  0x5873
#define VK_RADIO                        0x5874
#define VK_DISPLAY                      0x5875
#define VK_STOP                         0x5876
#define VK_RECORD                       0x5877
#define VK_FASTFWD                      0x5878
#define VK_REWIND                       0x5879
#define VK_SKIP                         0x587A
#define VK_REPLAY                       0x587B
#define VK_INFO                         0x587C
#define VK_GUIDE                        0x5803  // same as VK_PAD_Y
#define VK_TV                           0x5801  // same as VK_PAD_B
#define VK_MYTV                         0x587F
#define VK_MYMUSIC                      0x5880
#define VK_RECORDTV                     0x5881
#define VK_MYPICTURES                   0x5882
#define VK_MYVIDEOS                     0x5883
#define VK_ASPECT                       0x5884
#define VK_STAR                         0x5885
#define VK_POUND                        0x5886
#define VK_TITLE                        0x5887
#define VK_MCE                          0x5888
#define VK_KIOSK                        0x5889
#define VK_TTONOFF                      0x588A
#define VK_TTRED                        0x588B
#define VK_TTGREEN                      0x588C
#define VK_TTYELLOW                     0x588D
#define VK_TTBLUE                       0x588E
#define VK_TTINDEX                      0x588F
#define VK_TTORANGE                     0x5890
#define VK_GREENMODIFIER                0x5891
#define VK_ORANGEMODIFIER               0x5892
#define VK_DEADKEYMAKEUP                0x5893
#define VK_IPTV                         0x5894

//
// Codes returned for the gamepad input
//

#define VK_PAD_A                        0x5800
#define VK_PAD_B                        0x5801
#define VK_PAD_X                        0x5802
#define VK_PAD_Y                        0x5803
#define VK_PAD_RSHOULDER                0x5804
#define VK_PAD_LSHOULDER                0x5805
#define VK_PAD_LTRIGGER                 0x5806
#define VK_PAD_RTRIGGER                 0x5807

#define VK_PAD_DPAD_UP                  0x5810
#define VK_PAD_DPAD_DOWN                0x5811
#define VK_PAD_DPAD_LEFT                0x5812
#define VK_PAD_DPAD_RIGHT               0x5813
#define VK_PAD_START                    0x5814
#define VK_PAD_BACK                     0x5815
#define VK_PAD_LTHUMB_PRESS             0x5816
#define VK_PAD_RTHUMB_PRESS             0x5817

#define VK_PAD_LTHUMB_UP                0x5820
#define VK_PAD_LTHUMB_DOWN              0x5821
#define VK_PAD_LTHUMB_RIGHT             0x5822
#define VK_PAD_LTHUMB_LEFT              0x5823
#define VK_PAD_LTHUMB_UPLEFT            0x5824
#define VK_PAD_LTHUMB_UPRIGHT           0x5825
#define VK_PAD_LTHUMB_DOWNRIGHT         0x5826
#define VK_PAD_LTHUMB_DOWNLEFT          0x5827

#define VK_PAD_RTHUMB_UP                0x5830
#define VK_PAD_RTHUMB_DOWN              0x5831
#define VK_PAD_RTHUMB_RIGHT             0x5832
#define VK_PAD_RTHUMB_LEFT              0x5833
#define VK_PAD_RTHUMB_UPLEFT            0x5834
#define VK_PAD_RTHUMB_UPRIGHT           0x5835
#define VK_PAD_RTHUMB_DOWNRIGHT         0x5836
#define VK_PAD_RTHUMB_DOWNLEFT          0x5837


//
// Additonal codes returned for the "bigbutton" controller
//

#define VK_PAD_BIGBUTTON                0x5850


#define VKBD_DEFAULT                    0x00000000
#define VKBD_LATIN_FULL                 0x00000001
#define VKBD_LATIN_EMAIL                0x00000002
#define VKBD_LATIN_GAMERTAG             0x00000004
#define VKBD_LATIN_PHONE                0x00000008
#define VKBD_LATIN_IP_ADDRESS           0x00000010
#define VKBD_LATIN_NUMERIC              0x00000020
#define VKBD_LATIN_ALPHABET             0x00000040
#define VKBD_LATIN_PASSWORD             0x00000080
#define VKBD_LATIN_SUBSCRIPTION         0x00000100
#define VKBD_JAPANESE_FULL              0x00001000
#define VKBD_KOREAN_FULL                0x00002000
#define VKBD_TCH_FULL                   0x00004000
#define VKBD_RUSSIAN_FULL               0x00008000
// VKBD_LATIN_EXTENDED provides support for Eastern and Central European
// characters
#define VKBD_LATIN_EXTENDED             0x00010000
#define VKBD_SCH_FULL                   0x00020000
#define VKBD_JAPANESE_HIRAGANA          0x00040000
#define VKBD_JAPANESE_KATAKANA          0x00080000
// VKBD_GREEK_FULL and VKBD_CSH_FULL are LiveSignup-Only keyboards
#define VKBD_GREEK_FULL                 0x00100000
#define VKBD_CSH_FULL                   0x00200000 // Czech, Slovak, Hungarian

#define VKBD_SELECT_OK                  0x10000000
#define VKBD_HIGHLIGHT_TEXT             0x20000000


// Resolve set memory
pDmSetMemory DevSetMemory = NULL;
BOOL dbgInit = FALSE;
extern BOOL RunningFromUSB;

#ifdef _DEBUG

CRITICAL_SECTION dbgLock;

VOID DbgPrint( const CHAR* strFormat, ... ) {

	if(dbgInit == FALSE) {
		InitializeCriticalSection(&dbgLock);
		dbgInit = TRUE;
	}	

	CHAR buffer[ 1000 ];

	va_list pArgList;
	va_start( pArgList, strFormat );
	vsprintf_s( buffer, 1000, strFormat, pArgList );
	va_end(pArgList);

    printf("Shadow %s\n", buffer);

	EnterCriticalSection(&dbgLock);
	std::ofstream writeLog;
	writeLog.open(RunningFromUSB ? PATH_LOG_USB : PATH_LOG_HDD, std::ofstream::app);
	if (writeLog.is_open())	
	{
		writeLog.write(buffer, strlen(buffer));
		writeLog.write("\r\n", 2);
	}
	writeLog.close();
	LeaveCriticalSection(&dbgLock);
}

#endif


VOID returnToDashThread(){
	Sleep(3000);
	XSetLaunchData(NULL, 0);
	XamLoaderLaunchTitleEx( XLAUNCH_KEYWORD_DEFAULT_APP, NULL, NULL, 0);
}


static WCHAR sysMsgBuffer[100];
VOID sysMsgThreadDelay(WCHAR* msg){
	//while(!dashLoaded){
	//	Sleep(2500);
	//}
	Sleep(8000);
	XNotifyUI(msg);
}

VOID sysMsgThread(WCHAR* msg){
	XNotifyUI(msg);
}

VOID launchSysMsg(WCHAR* msg, int delay){
	memcpy(sysMsgBuffer, msg, (wcslen(msg)*sizeof(WCHAR))+2);
	HANDLE hThread;
	DWORD dwThreadId;
	if(delay!=60000 && delay>0){
		Sleep(delay);
		ExCreateThread(&hThread, 0, &dwThreadId, (VOID*) XapiThreadStartup , (LPTHREAD_START_ROUTINE)sysMsgThread, sysMsgBuffer, 0x2);
	}else
		ExCreateThread(&hThread, 0, &dwThreadId, (VOID*) XapiThreadStartup , (LPTHREAD_START_ROUTINE)sysMsgThreadDelay, sysMsgBuffer, 0x2);

	XSetThreadProcessor( hThread, 4 );
	ResumeThread(hThread);
	CloseHandle(hThread);
}

VOID returnToDash(WCHAR* msg){
	HANDLE hThread;
	DWORD dwThreadId;
	hThread = CreateThread( 0, 0, (LPTHREAD_START_ROUTINE)returnToDashThread, 0, CREATE_SUSPENDED, &dwThreadId );
	XSetThreadProcessor(hThread, 4);
	SetThreadPriority(hThread, THREAD_PRIORITY_TIME_CRITICAL);
	ResumeThread(hThread);
	CloseHandle(hThread);
	if(msg) launchSysMsg(msg, 0);
	Sleep(500);
}


PWCHAR charToWChar(__in LPCSTR c_buffer) {
	int wchars_num = MultiByteToWideChar(CP_ACP, 0, c_buffer, -1, NULL, 0);
	PWCHAR c_wbuffer = new WCHAR[wchars_num];
	MultiByteToWideChar(CP_ACP, 0, c_buffer, -1, (LPWSTR)c_wbuffer, wchars_num);
	return c_wbuffer;
}

int toWCHAR(char* input, WCHAR* output){
	if(!input || !output) return 0;
	int len = strlen(input);

	memset(output, 0, (len*2)+2); //convert to wide string because xdk functions don't fucking work
	for(int i=1, b=0; b<len; i+=2){
		((char*)output)[i]=input[b];
		b++;
	}
	return len;
}

BOOL XeKeysPkcs1Verify(const BYTE* pbHash, const BYTE* pbSig, XECRYPT_RSA* pRsa) {
	BYTE scratch[256];
	DWORD val = pRsa->cqw << 3;
	if (val <= 0x200) {
		XeCryptBnQw_SwapDwQwLeBe((QWORD*)pbSig, (QWORD*)scratch, val >> 3);
		if (XeCryptBnQwNeRsaPubCrypt((QWORD*)scratch, (QWORD*)scratch, pRsa) == 0) return FALSE;
		XeCryptBnQw_SwapDwQwLeBe((QWORD*)scratch, (QWORD*)scratch, val >> 3);
		return XeCryptBnDwLePkcs1Verify((const PBYTE)pbHash, scratch, val);
	}
	else return FALSE;
}

VOID PatchInJump(DWORD* Address, DWORD Destination, BOOL Linked) {
	Address[0] = 0x3D600000 + ((Destination >> 16) & 0xFFFF);
	if(Destination & 0x8000) Address[0] += 1;
	Address[1] = 0x396B0000 + (Destination & 0xFFFF);
	Address[2] = 0x7D6903A6;
	Address[3] = Linked ? 0x4E800421 : 0x4E800420;
}

VOID PatchInBranch(DWORD* Address, DWORD Destination, BOOL Linked) {
	Address[0] = (0x48000000 + ((Destination - (DWORD)Address) & 0x3FFFFFF));
	if(Linked) Address[0] += 1;
}

FARPROC ResolveFunction(CHAR* ModuleName, DWORD Ordinal) {
	HMODULE mHandle = GetModuleHandle(ModuleName);
	return (mHandle == NULL) ? NULL : GetProcAddress(mHandle, (LPCSTR)Ordinal);
}
DWORD PatchModuleImport(CHAR* Module, CHAR* ImportedModuleName, DWORD Ordinal, DWORD PatchAddress) {
	LDR_DATA_TABLE_ENTRY* moduleHandle = (LDR_DATA_TABLE_ENTRY*)GetModuleHandle(Module);
	return (moduleHandle == NULL) ? S_FALSE : PatchModuleImport(moduleHandle, ImportedModuleName, Ordinal, PatchAddress);
}
DWORD PatchModuleImport(PLDR_DATA_TABLE_ENTRY Module, CHAR* ImportedModuleName, DWORD Ordinal, DWORD PatchAddress) {

	// First resolve this imports address
	DWORD address = (DWORD)ResolveFunction(ImportedModuleName, Ordinal);
	if(address == NULL)
		return S_FALSE;

	// Get our header field from this module
	VOID* headerBase = Module->XexHeaderBase;
	PXEX_IMPORT_DESCRIPTOR importDesc = (PXEX_IMPORT_DESCRIPTOR)RtlImageXexHeaderField(headerBase, 0x000103FF);
	if(importDesc == NULL)
		return S_FALSE;

	// Our result
	DWORD result = 2; // No occurances patched

	// Get our string table position
	CHAR* stringTable = (CHAR*)(importDesc + 1);
	
	// Get our first entry
	XEX_IMPORT_TABLE_ORG* importTable = (XEX_IMPORT_TABLE_ORG*)(stringTable + importDesc->NameTableSize);

	// Loop through our table
	for(DWORD x = 0; x < importDesc->ModuleCount; x++) {
		
		// Go through and search all addresses for something that links
		DWORD* importAdd = (DWORD*)(importTable + 1);
		for(DWORD y = 0; y < importTable->ImportTable.ImportCount; y++) {

			// Check the address of this import
			DWORD value = *((DWORD*)importAdd[y]);
			if(value == address) {

				// We found a matching address address
				SetMemory((DWORD*)importAdd[y], &PatchAddress, 4);
				DWORD newCode[4];
				PatchInJump(newCode, PatchAddress, FALSE);
				SetMemory((DWORD*)importAdd[y + 1], newCode, 16);

				// We patched at least one occurence
				result = S_OK;
			}
		}

		// Goto the next table
		importTable = (XEX_IMPORT_TABLE_ORG*)(((BYTE*)importTable) + importTable->TableSize);
	}

	// Return our result
	return result;
}

HRESULT CreateSymbolicLink(CHAR* szDrive, CHAR* szDeviceName, BOOL System) {

	// Setup our path
	CHAR szDestinationDrive[MAX_PATH];
	sprintf_s(szDestinationDrive, MAX_PATH, System ? "\\System??\\%s" : "\\??\\%s", szDrive);

	// Setup our strings
	ANSI_STRING linkname, devicename;
	RtlInitAnsiString(&linkname, szDestinationDrive);
	RtlInitAnsiString(&devicename, szDeviceName);

	//check if already mapped
	if(FileExists(szDrive))
		return S_OK;

	// Create finally
	NTSTATUS status = ObCreateSymbolicLink(&linkname, &devicename);
	return (status >= 0) ? S_OK : S_FALSE;
}
HRESULT DeleteSymbolicLink(CHAR* szDrive, BOOL System) {

	// Setup our path
	CHAR szDestinationDrive[MAX_PATH];
	sprintf_s(szDestinationDrive, MAX_PATH, System ? "\\System??\\%s" : "\\??\\%s", szDrive);

	// Setup our string
	ANSI_STRING linkname;
	RtlInitAnsiString(&linkname, szDestinationDrive);
	
	// Delete finally
	NTSTATUS status = ObDeleteSymbolicLink(&linkname);
	return (status >= 0) ? S_OK : S_FALSE;
}
BOOL CReadFile(const CHAR * FileName, MemoryBuffer &pBuffer) {

	HANDLE hFile; DWORD dwFileSize, dwNumberOfBytesRead;
	hFile = CreateFile(FileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE) {
		DbgPrint("CReadFile - CreateFile failed");
		return FALSE;
	}
	dwFileSize = GetFileSize(hFile, NULL);
	PBYTE lpBuffer = (BYTE*)malloc(dwFileSize);
	if(lpBuffer == NULL) {
		CloseHandle(hFile);
		DbgPrint("CReadFile - malloc failed");
		return FALSE;
	}
	if(ReadFile(hFile, lpBuffer, dwFileSize, &dwNumberOfBytesRead, NULL) == FALSE) {
		free(lpBuffer);
		CloseHandle(hFile);
		DbgPrint("CReadFile - ReadFile failed");
		return FALSE;
	}
	else if (dwNumberOfBytesRead != dwFileSize) {
		free(lpBuffer);
		CloseHandle(hFile);
		DbgPrint("CReadFile - Failed to read all the bytes");
		return FALSE;
	}
	CloseHandle(hFile);
	pBuffer.Add(lpBuffer, dwFileSize);
	free(lpBuffer);
	return TRUE;
}
BOOL CWriteFile(const CHAR* FilePath, const VOID* Data, DWORD Size) {
	
	// Open our file
	HANDLE fHandle = CreateFile(FilePath, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(fHandle == INVALID_HANDLE_VALUE) {
		DbgPrint("CWriteFile - CreateFile failed");
		return FALSE;
	}

	// Write our data and close
	DWORD writeSize = Size;
	if(WriteFile(fHandle, Data, writeSize, &writeSize, NULL) != TRUE) {
		DbgPrint("CWriteFile - WriteFile failed");
		return FALSE;
	}
	CloseHandle(fHandle);

	// All done
	return TRUE;
}
BOOL FileExists(LPCSTR lpFileName) {

	// Try and get the file attributes.
	if(GetFileAttributes(lpFileName) == -1) {
		DWORD lastError = GetLastError();
		if(lastError == ERROR_FILE_NOT_FOUND || lastError == ERROR_PATH_NOT_FOUND)
			return FALSE;
	}

	// The file must exist if we got this far..
	return TRUE;
}

BOOL IsTrayOpen() { 
	unsigned char msg[0x10]; 
	unsigned char resp[0x10]; 
	memset(msg, 0x0, 0x10); 
	msg[0] = 0xa; 
	HalSendSMCMessage(msg, resp); 

	if (resp[1] ==  0x60) 
		return true; 
	else 
		return false; 
}

BOOL pfShow = (BOOL)0xDEADBEEF;  //flag to init values
BOOL pfShowMovie;
BOOL pfPlaySound;
BOOL pfShowIPTV;

VOID toggleNotify(BOOL on){
	if((int)pfShow==0xDEADBEEF) //init values
		XNotifyUIGetOptions(&pfShow, &pfShowMovie, &pfPlaySound, &pfShowIPTV);
	
	if(!on){
		//XNotifyUISetOptions(false, false, false, true);
		XNotifyUISetOptions(pfShow, pfShowMovie, pfPlaySound, pfShowIPTV);  //set back original values
	}else{
		XNotifyUISetOptions(true, true, true, true);  //turn on notifications so XBLSE msgs always show..
	}
	Sleep(500);
}

VOID XNotifyDoQueueUI(PWCHAR pwszStringParam) {
	toggleNotify(true);
	XNotifyQueueUI(XNOTIFYUI_TYPE_PREFERRED_REVIEW, XUSER_INDEX_ANY, XNOTIFYUI_PRIORITY_HIGH, pwszStringParam, NULL);
	toggleNotify(false);
}

//Use this one!
VOID XNotifyUI(PWCHAR pwszStringParam)
{
	if (KeGetCurrentProcessType() != PROC_USER)
	{
		HANDLE th = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)XNotifyDoQueueUI, (LPVOID)pwszStringParam, CREATE_SUSPENDED, NULL);
		if (th == NULL) return;
		ResumeThread(th);
	}
	else
		XNotifyDoQueueUI(pwszStringParam);	
}

HRESULT SetMemory(VOID* Destination, VOID* Source, DWORD Length) {

	// Try to resolve our function
	if(DevSetMemory == NULL)
		DevSetMemory = (pDmSetMemory)ResolveFunction("xbdm.xex", 40);
	
	// Now lets try to set our memory
	if(DevSetMemory == NULL) {
		memcpy(Destination, Source, Length);
		return ERROR_SUCCESS;
	} else {
		if(DevSetMemory(Destination, Length, Source, NULL) == MAKE_HRESULT(0, 0x2da, 0))
			return ERROR_SUCCESS;
	}

	// We have a problem..
	return E_FAIL;
}

VOID __declspec(naked) GLPR(VOID)
{
	__asm
	{
		std     r14, -0x98(sp)
		std     r15, -0x90(sp)
		std     r16, -0x88(sp)
		std     r17, -0x80(sp)
		std     r18, -0x78(sp)
		std     r19, -0x70(sp)
		std     r20, -0x68(sp)
		std     r21, -0x60(sp)
		std     r22, -0x58(sp)
		std     r23, -0x50(sp)
		std     r24, -0x48(sp)
		std     r25, -0x40(sp)
		std     r26, -0x38(sp)
		std     r27, -0x30(sp)
		std     r28, -0x28(sp)
		std     r29, -0x20(sp)
		std     r30, -0x18(sp)
		std     r31, -0x10(sp)
		stw     r12, -0x8(sp)
		blr
	}
}
DWORD RelinkGPLR(DWORD SFSOffset, PDWORD SaveStubAddress, PDWORD OriginalAddress)
{
	DWORD Instruction = 0, Replacing;
	PDWORD Saver = (PDWORD)GLPR;
	if(SFSOffset & 0x2000000)
	{
		SFSOffset = SFSOffset | 0xFC000000;
	}
	Replacing = OriginalAddress[SFSOffset / 4];
	for(int i = 0; i < 20; i++)
	{
		if(Replacing == Saver[i])
		{
			DWORD NewOffset = (DWORD)&Saver[i]-(DWORD)SaveStubAddress;
			Instruction = 0x48000001 | (NewOffset & 0x3FFFFFC);
		}
	}
	return Instruction;
}
VOID HookFunctionStart(PDWORD Address, PDWORD SaveStub, DWORD Destination)
{
	if((SaveStub != NULL) && (Address != NULL)) // Make sure they are not nothing.
	{
		DWORD AddressRelocation = (DWORD)(&Address[4]); // Replacing 4 instructions with a jump, this is the stub return address
		if(AddressRelocation & 0x8000)
		{
			SaveStub[0] = 0x3D600000 + (((AddressRelocation >> 16) & 0xFFFF) + 1); // lis r11, 0 | Load Immediate Shifted
		}
		else
		{
			SaveStub[0] = 0x3D600000 + ((AddressRelocation >> 16) & 0xFFFF); // lis r11, 0 | Load Immediate Shifted
		}
		SaveStub[1] = 0x396B0000 + (AddressRelocation & 0xFFFF); // addi r11, r11, (value of AddressRelocation & 0xFFFF) | Add Immediate
		SaveStub[2] = 0x7D6903A6; // mtspr CTR, r11 | Move to Special-Purpose Register CTR
		// Instructions [3] through [6] are replaced with the original instructions from the function hook
		// Copy original instructions over, relink stack frame saves to local ones
		for(int i = 0; i < 4; i++)
		{
			if((Address[i] & 0x48000003) == 0x48000001)
			{
				SaveStub[i + 3] = RelinkGPLR((Address[i] & ~0x48000003), &SaveStub[i + 3], &Address[i]);
			}
			else
			{
				SaveStub[i + 3] = Address[i];
			}
		}
		SaveStub[7] = 0x4E800420; // Branch unconditionally
		__dcbst(0, SaveStub); // Data Cache Block Store | Allows a program to copy the contents of a modified block to main memory.
		__sync(); // Synchronize | Ensure the dcbst instruction has completed.
		__isync(); // Instruction Synchronize | Refetches any instructions that might have been fetched prior to this instruction.
		PatchInJump(Address, Destination, FALSE); // Redirect Function to ours

		/*
		* So in the end, this will produce:
		*
		* lis r11, ((AddressRelocation >> 16) & 0xFFFF [+ 1])
		* addi r11, r11, (AddressRelocation & 0xFFFF)
		* mtspr CTR, r11
		* branch (?Destination?)
		* dcbst 0, (SaveStub)
		* sync
		*/
	}
}

UINT32 resolveFunct(char* modname, UINT32 ord) 
 { 
	UINT32 ptr32 = 0, ret = 0, ptr2 = 0; 
	ret = XexGetModuleHandle(modname, (PHANDLE)&ptr32); 
	if(ret == 0)
	{ 
		ret = XexGetProcedureAddress((HANDLE)ptr32, ord, &ptr2); 
		if(ptr2 != 0) 
		return(ptr2); 
	} 
	return(0); 
 }

DWORD makeBranch(DWORD branchAddr, DWORD destination, BOOL linked) {
	return (0x48000000)|((destination-branchAddr)&0x03FFFFFF)|(DWORD)linked;
}

DWORD ApplyPatches(const VOID* DefaultPatches) {

	// Read our file
	DWORD patchCount = 0;
	MemoryBuffer mbPatches;
	DWORD* patchData = (DWORD*)DefaultPatches;
	// Make sure we have patches...
	if(patchData == NULL) {
		return 0;
	}

	// Apply our patches	
	while(*patchData != 0xFFFFFFFF) {

		BOOL inHvMode = (patchData[0] < 0x40000);
		QWORD patchAddr = inHvMode ? (0x200000000 * (patchData[0] / 0x10000)) + patchData[0] : (QWORD)patchData[0];
		
		if(inHvMode)
			HvPokeBytes(patchAddr, &patchData[2], patchData[1] * sizeof(DWORD));
		else
			SetMemory((VOID*)patchData[0], &patchData[2], patchData[1] * sizeof(DWORD));

		patchData += (patchData[1] + 2);
		patchCount++;
	}

	return patchCount;
}

DWORD ApplyPatches(CHAR* FilePath) {

	// Read our file
	DWORD patchCount = 0;
	MemoryBuffer mbPatches;
	DWORD* patchData;
	
	// Check if we have our override patches
	if(FileExists(FilePath)) {
		if(!CReadFile(FilePath, mbPatches))
			return patchCount;
		
		// Set our patch data now..
		patchData = (DWORD*)mbPatches.GetData();
	}
	
	// Make sure we have patches...
	if(patchData == NULL) {
		return 0;
	}

	// Apply our patches	
	while(*patchData != 0xFFFFFFFF) {

		BOOL inHvMode = (patchData[0] < 0x40000);
		QWORD patchAddr = inHvMode ? (0x200000000 * (patchData[0] / 0x10000)) + patchData[0] : (QWORD)patchData[0];
		
		if(inHvMode)
			HvPokeBytes(patchAddr, &patchData[2], patchData[1] * sizeof(DWORD));
		else
			SetMemory((VOID*)patchData[0], &patchData[2], patchData[1] * sizeof(DWORD));

		patchData += (patchData[1] + 2);
		patchCount++;
	}

	return patchCount;
}