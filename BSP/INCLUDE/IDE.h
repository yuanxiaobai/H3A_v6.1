#ifndef __IDE_H
#define __IDE_H

#define NULL 0

#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

/***************************************************************************************/
/** 驱动参数配置																	   */
/***************************************************************************************/
#define MAX_DEVICE 	2					/*定义设备数,由于只有主和从设备,所以最大值为2*/
#define TIMEOUTSET		0x0005ffff		/*超时响应设备(与CPU的速度有关,没有准确的时间)*/


/****************************************************************************************/
/**	以下为本驱动定义部份，用户不需改动													*/
/****************************************************************************************/
/*ATA 指令代码*/
#define 	IDE_CMD_ATAPI_RESET      		0x08
#define 	IDE_CMD_RECALIBRATE      		0x10
#define 	IDE_CMD_READ             		0x20	// 读扇区命令
#define 	IDE_CMD_WRITE            		0x30	// 写扇区命令
#define 	IDE_CMD_VERIFY           		0x40
#define 	IDE_CMD_SEEK             		0x70
#define		IDE_CMD_EXEC_DIAGNOSE    		0x90
#define		IDE_CMD_SET_DRIVE_PARAMETERS 	0x91
#define 	IDE_CMD_READ_MULTIPLE    		0xC4	// 多扇区读
#define 	IDE_CMD_WRITE_MULTIPLE   		0xC5	// 多扇区写
#define 	IDE_CMD_SET_MULTIPLE    		0xC6
#define 	IDE_CMD_READ_DMA         		0xC8
#define 	IDE_CMD_WRITE_DMA             	0xCA
#define 	IDE_CMD_GET_MEDIA_STATUS      	0xDA
#define    	IDE_CMD_STANDBY_IMMEDIATE		0xE0	// Standby Immediate
#define    	IDE_CMD_IDLE_IMMEDIATE 			0xE1	// Idle Immediate
#define 	IDE_CMD_SETFEATURES				0xEF
#define 	IDE_CMD_IDENTIFY              	0xEC
#define 	IDE_CMD_MEDIA_EJECT           	0xED


/*状态寄存器相关位*/
#define		ATA_STAT_REG_ERR 				0x01	/*设备发生了错误*/
#define		ATA_STAT_REG_IDX  				0x02  	/**/
#define		ATA_STAT_REG_CORR  				0x04  	/**/
#define		ATA_STAT_REG_DRQ  				0x08 	/*有数据传输请求*/
#define		ATA_STAT_REG_DSC  				0x10 	/**/
#define		ATA_STAT_REG_DF   				0x20 	/**/
#define		ATA_STAT_REG_DRDY  				0x40 	/*设备准备好*/
#define		ATA_STAT_REG_BSY  				0x80 	/*设备忙*/
#define		ATA_STAT_BSY_DRDY		(ATA_STAT_REG_BSY+ATA_STAT_REG_DRDY)
#define		ATA_STAT_BSY_DRQ		(ATA_STAT_REG_BSY+ATA_STAT_REG_DRQ)

/*设备磁头寄存器*/
#define		ATA_DevReg_DEV0  				0x00	/*设备为主盘*/
#define		ATA_DevReg_DEV1  				0x10	/*设备为从盘*/
#define		ATA_DevReg_b5   				0x20	/*保留位，为1*/
#define		ATA_DevReg_LBA  				0x40	/*模式选择位*/
#define		ATA_DevReg_b7   				0x80	/*保留位，为1*/

/*控制寄存器*/
#define 	CF_SOFT_RESET					0x04	/*软件复位有效*/
#define 	CF_DISABLE_INT					0x00	/*禁能中断*/
#define 	CF_ENABLE_INT					0x02	/*使能中断*/


/*错误代码由16位二进制数组成,低8位与ATA错误寄存器一致,高8位自定义*/
#define ATA_EER_REG_AMNF					0x01	/*一般错误*/
#define ATA_EER_REG_ABRT 					0x04	/*指令无效出错*/
#define ATA_EER_REG_IDNF 					0x10	/*寻扇区地址出错*/
#define ATA_EER_REG_UNC 					0x40	/*发生了不可纠正的错误*/
#define ATA_EER_REG_BBK						0x80	/*发现错误块*/
/*自定义*/
#define CARD_IS_FALSE						0x00ff	/*CF卡不存在或无效*/
#define CARD_IS_TRUE						0x0000	/*CF卡有效*/
#define CARD_TIMEOUT						0x0100	/*对CF卡操作超时出错*/


#define THIS_DEVICE			((ATA_DevReg&0x10)>>4)	/*当前操作的设备，ATA_SelectDevice函数选择了主或从设备，通过该操作可以确定刚才选定的设备*/

/*设备识别信息*/
/*全部设备信息*/
typedef struct _IDENTIFY_DATA
{
	Uint16 GeneralConfiguration;            // 00  	 普通设置-CF卡标志0x848A
	Uint16 NumberOfCylinders;               // 1   	 默认柱面数
	Uint16 Reserved1;                       // 2
	Uint16 NumberOfHeads;                   // 3   	 默认磁头数
	Uint16 UnformattedBytesPerTrack;      	// 4   	 在2.0规范已不使用
	Uint16 UnformattedBytesPerSector;     	// 5   	 在2.0规范已不使用
	Uint16 SectorsPerTrack;                 // 6   	 每磁道默认扇区数
	Uint32 SectorsPerCard;                  // 7-8 	 每卡扇区数(Word 7=MSW,Word 8=LSW)
	Uint16 VendorUnique;					// 9 	 在2.0规范已不使用
	Uint16 SerialNumber[10];                // 10-19 ASCII序列号（靠右填写）
	Uint16 BufferType;                      // 20 	 在2.0规范已不使用
	Uint16 BufferSectorSize;                // 21    在2.0规范已不使用
	Uint16 NumberOfEccBytes;                // 22    读/写长指令时的ECC字节数
	Uint16 FirmwareRevision[4];             // 23-26 ASCII固件版本。大端格式
	Uint16 ModelNumber[20];                 // 27-46 ASCII模式号（靠左填写），大端格式
	Uint16 MaximumBlockTransfer;            //*47    多重 读/写指令最大扇区号。
	Uint16 Reserved2;                    	// 48
	Uint16 Capabilities;                    // 49
	Uint16 Reserved3;                       // 50

	Uint16 PioCycleTimingMode;             	//*51    PIO数据传输周期时序模式

	Uint16 DmaCycleTimingMode;             	// 52    在2.0规范已不使用
	Uint16 TranslationFieldsValid;          // 53    0位为1,Word54 to 58 有效;1位为1,Word64 to 70 有效

	Uint16 NumberOfCurrentCylinders;      	// 54    当前柱面数
	Uint16 NumberOfCurrentHeads;            // 55    当前磁头数
	Uint16 CurrentSectorsPerTrack;          // 56    当前每磁道扇区数
	Uint32 CurrentSectorCapacity;           // 57-58 当前扇区容量（LBAs）(Word 58=MSW,Word 57=LSW)

	Uint16 CurrentMultiSectorSetting;       //*59    位8为1,则位0-7,指出可多扇区读写的扇区数
	Uint32 UserAddressableSectors;          // 60-61 LAB模式下可被寻址的扇区数
	Uint16 Reserved4[2] ;           		// 62-63
	Uint16 AdvancedPIOModes ;               // 64    在2.0规范使用
	Uint16 Reserved6[2] ;         			// 65-66
	Uint16 MinimumPIOCycleTime;             // 67    非流控制下最小PIO传输周期时间
	Uint16 MinimumPIOCycleTimeIORDY; 		// 68    IORDY流控制小最小PIO传输周期时间
	Uint16 Reserved7[10];                   // 69-79
	Uint32 AtaVersion;           			// 80-81 CF卡返回0
	Uint16 FeaturesCommandSupported[3];		// 82-84 特征／命令集技持
	Uint16 FeaturesCommandEnabled[3];    	// 85-87 特征／命令集使能
	Uint16 Reserved8;       				// 88
	Uint16 MajorRevision;                   // 89    安全单位完全擦除的时间要求
	Uint16 MinorRevision;                   // 90    增强型安全单位完全擦除的时间要求
	Uint16 PowerManagementValue;			// 91	 当前高级电源管理值									//     91
	Uint16 Reserved9[36];                   // 92-127
	Uint16 SecurityStatus;					// 128   安全状态
	Uint16 VendorUniqueBytes[32];			// 129-159
	Uint16 PowerRequirementDescription; 	// 160   电源要求描述
	Uint16 Reserved10;						// 161
	Uint16 KeyManagementSupported;        	// 162   按键管理表
	Uint16 Reserved11[83];                  // 163-255

} CF_IDENTIFY_DATA, *PCF_IDENTIFY_DATA;

/*设备基本信息*/
typedef struct _ATA_IDENTIFY_DATA
{
	Uint16 NumberOfCylinders;               // 1   	 默认柱面数
	Uint16 NumberOfHeads;                   // 3   	 默认磁头数
	Uint16 SectorsPerTrack;                 // 6   	 每磁道默认扇区数
	Uint32 CurrentSectorCapacity;           // 57-58 当前扇区容量（LBAs）(Word 58=MSW,Word 57=LSW)

} ATA_IDENTIFY_DATA, *PATA_IDENTIFY_DATA;


/*设备信息结构*/
typedef struct
{
	Uint8   			ATAIsOK;			/*设备正常为1，无效或有错为0*/
	Uint16 				ERRCODE;			/*设备出错代码*/
	Uint32 				ERRSECTOR;			/*读写扇区是出错的扇区号*/
	ATA_IDENTIFY_DATA	INFODATA;			/*设备的基本信息*/
}ATADEVICE, *PATADEVICE;

extern ATADEVICE 	ATA[MAX_DEVICE];		/*设备识别信息识别结构*/



/******************************************************************************************/
/*相关函数原型*/
/******************************************************************************************/

//****************************************************************************************
/*用户使用函数*/
void 	USB_detecte( void );
void 	ATA_INI( void );																/*总线设置与初始化，ATA设备初始化*/
void  	ATA_FindIDEDevice( void );													/*硬件复位,查找IDE设备，并初始化*/

Uint8 	ATA_IdleImmediate( Uint8 Device );				    						/*立即进入空闲状态(硬盘转动)*/
Uint8 	ATA_StandbyImmediate( Uint8 Device );											/*立即进入待机状态(硬盘停转)*/
Uint8 	ATA_ReadSector( Uint8 Device, Uint16 *Buffer, Uint32 Sector, Uint8 count );		/*读出扇区数据函数*/
Uint8 	ATA_WriteSector( Uint8 Device, Uint16 * Buffer, Uint32 Sector , Uint8 count );	/*写入设备扇区莺�*/
Uint8 	ATA_IdentifyDrive( Uint8 Device, void *PTR );									/*获取设备信息*/

//****************************************************************************************
/*驱动内部使用函数*/
Uint8 	ATA_IssueIDEIdentify( Uint8 Device );				/*设备识别,获取设备基本信息*/

Uint8 	ATA_SetFeature( Uint8 Device );					/*设备总线特性设置*/
void  	ATA_WriteSetting( Uint32 Sectors , Uint8 Count );	/*写IDE多数扇区数据*/
void  	ATA_ReadSetting( Uint32 Sectors , Uint8 Count );	/*写IDE多数扇区数据*/
void 	ATA_WriteData512B( Uint16 * Buffer );				/*连续写512字节数据*/
void 	ATA_ReadData512B( Uint16 * Buffer );				/*连续读512字节数据*/

#endif
