<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित CCISS_IOCTLH
#घोषणा CCISS_IOCTLH

#समावेश <uapi/linux/cciss_ioctl.h>

#अगर_घोषित CONFIG_COMPAT

/* 32 bit compatible ioctl काष्ठाs */
प्रकार काष्ठा _IOCTL32_Command_काष्ठा अणु
  LUNAddr_काष्ठा	   LUN_info;
  RequestBlock_काष्ठा      Request;
  ErrorInfo_काष्ठा  	   error_info;
  WORD			   buf_size;  /* size in bytes of the buf */
  __u32			   buf; /* 32 bit poपूर्णांकer to data buffer */
पूर्ण IOCTL32_Command_काष्ठा;

प्रकार काष्ठा _BIG_IOCTL32_Command_काष्ठा अणु
  LUNAddr_काष्ठा	   LUN_info;
  RequestBlock_काष्ठा      Request;
  ErrorInfo_काष्ठा  	   error_info;
  DWORD			   दो_स्मृति_size; /* < MAX_KMALLOC_SIZE in cciss.c */
  DWORD			   buf_size;    /* size in bytes of the buf */
  				        /* < दो_स्मृति_size * MAXSGENTRIES */
  __u32 		buf;	/* 32 bit poपूर्णांकer to data buffer */
पूर्ण BIG_IOCTL32_Command_काष्ठा;

#घोषणा CCISS_PASSTHRU32   _IOWR(CCISS_IOC_MAGIC, 11, IOCTL32_Command_काष्ठा)
#घोषणा CCISS_BIG_PASSTHRU32 _IOWR(CCISS_IOC_MAGIC, 18, BIG_IOCTL32_Command_काष्ठा)

#पूर्ण_अगर /* CONFIG_COMPAT */
#पूर्ण_अगर  
