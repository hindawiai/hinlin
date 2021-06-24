<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPICCISS_IOCTLH
#घोषणा _UAPICCISS_IOCTLH

#समावेश <linux/types.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/cciss_defs.h>

#घोषणा CCISS_IOC_MAGIC 'B'


प्रकार काष्ठा _cciss_pci_info_काष्ठा
अणु
	अचिन्हित अक्षर 	bus;
	अचिन्हित अक्षर 	dev_fn;
	अचिन्हित लघु	करोमुख्य;
	__u32 		board_id;
पूर्ण cciss_pci_info_काष्ठा; 

प्रकार काष्ठा _cciss_coalपूर्णांक_काष्ठा
अणु
	__u32  delay;
	__u32  count;
पूर्ण cciss_coalपूर्णांक_काष्ठा;

प्रकार अक्षर NodeName_type[16];

प्रकार __u32 Heartbeat_type;

#घोषणा CISS_PARSCSIU2 	0x0001
#घोषणा CISS_PARCSCIU3 	0x0002
#घोषणा CISS_FIBRE1G	0x0100
#घोषणा CISS_FIBRE2G	0x0200
प्रकार __u32 BusTypes_type;

प्रकार अक्षर FirmwareVer_type[4];
प्रकार __u32 DriverVer_type;

#घोषणा MAX_KMALLOC_SIZE 128000

प्रकार काष्ठा _IOCTL_Command_काष्ठा अणु
  LUNAddr_काष्ठा	   LUN_info;
  RequestBlock_काष्ठा      Request;
  ErrorInfo_काष्ठा  	   error_info; 
  WORD			   buf_size;  /* size in bytes of the buf */
  BYTE			   __user *buf;
पूर्ण IOCTL_Command_काष्ठा;

प्रकार काष्ठा _BIG_IOCTL_Command_काष्ठा अणु
  LUNAddr_काष्ठा	   LUN_info;
  RequestBlock_काष्ठा      Request;
  ErrorInfo_काष्ठा  	   error_info;
  DWORD			   दो_स्मृति_size; /* < MAX_KMALLOC_SIZE in cciss.c */
  DWORD			   buf_size;    /* size in bytes of the buf */
  				        /* < दो_स्मृति_size * MAXSGENTRIES */
  BYTE			   __user *buf;
पूर्ण BIG_IOCTL_Command_काष्ठा;

प्रकार काष्ठा _LogvolInfo_काष्ठाअणु
	__u32	LunID;
	पूर्णांक	num_खोलोs;  /* number of खोलोs on the logical volume */
	पूर्णांक	num_parts;  /* number of partitions configured on logvol */
पूर्ण LogvolInfo_काष्ठा;

#घोषणा CCISS_GETPCIINFO _IOR(CCISS_IOC_MAGIC, 1, cciss_pci_info_काष्ठा)

#घोषणा CCISS_GETINTINFO _IOR(CCISS_IOC_MAGIC, 2, cciss_coalपूर्णांक_काष्ठा)
#घोषणा CCISS_SETINTINFO _IOW(CCISS_IOC_MAGIC, 3, cciss_coalपूर्णांक_काष्ठा)

#घोषणा CCISS_GETNODENAME _IOR(CCISS_IOC_MAGIC, 4, NodeName_type)
#घोषणा CCISS_SETNODENAME _IOW(CCISS_IOC_MAGIC, 5, NodeName_type)

#घोषणा CCISS_GETHEARTBEAT _IOR(CCISS_IOC_MAGIC, 6, Heartbeat_type)
#घोषणा CCISS_GETBUSTYPES  _IOR(CCISS_IOC_MAGIC, 7, BusTypes_type)
#घोषणा CCISS_GETFIRMVER   _IOR(CCISS_IOC_MAGIC, 8, FirmwareVer_type)
#घोषणा CCISS_GETDRIVVER   _IOR(CCISS_IOC_MAGIC, 9, DriverVer_type)
#घोषणा CCISS_REVALIDVOLS  _IO(CCISS_IOC_MAGIC, 10)
#घोषणा CCISS_PASSTHRU	   _IOWR(CCISS_IOC_MAGIC, 11, IOCTL_Command_काष्ठा)
#घोषणा CCISS_DEREGDISK	   _IO(CCISS_IOC_MAGIC, 12)

/* no दीर्घer used... use REGNEWD instead */ 
#घोषणा CCISS_REGNEWDISK  _IOW(CCISS_IOC_MAGIC, 13, पूर्णांक)

#घोषणा CCISS_REGNEWD	   _IO(CCISS_IOC_MAGIC, 14)
#घोषणा CCISS_RESCANDISK   _IO(CCISS_IOC_MAGIC, 16)
#घोषणा CCISS_GETLUNINFO   _IOR(CCISS_IOC_MAGIC, 17, LogvolInfo_काष्ठा)
#घोषणा CCISS_BIG_PASSTHRU _IOWR(CCISS_IOC_MAGIC, 18, BIG_IOCTL_Command_काष्ठा)

#पूर्ण_अगर /* _UAPICCISS_IOCTLH */
