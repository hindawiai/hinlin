<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SCSI_IOCTL_H
#घोषणा _SCSI_IOCTL_H 

#घोषणा SCSI_IOCTL_SEND_COMMAND 1
#घोषणा SCSI_IOCTL_TEST_UNIT_READY 2
#घोषणा SCSI_IOCTL_BENCHMARK_COMMAND 3
#घोषणा SCSI_IOCTL_SYNC 4			/* Request synchronous parameters */
#घोषणा SCSI_IOCTL_START_UNIT 5
#घोषणा SCSI_IOCTL_STOP_UNIT 6
/* The करोor lock/unlock स्थिरants are compatible with Sun स्थिरants क्रम
   the cdrom */
#घोषणा SCSI_IOCTL_DOORLOCK 0x5380		/* lock the eject mechanism */
#घोषणा SCSI_IOCTL_DOORUNLOCK 0x5381		/* unlock the mechanism	  */

#घोषणा	SCSI_REMOVAL_PREVENT	1
#घोषणा	SCSI_REMOVAL_ALLOW	0

#अगर_घोषित __KERNEL__

काष्ठा scsi_device;

/*
 * Structures used क्रम scsi_ioctl et al.
 */

प्रकार काष्ठा scsi_ioctl_command अणु
	अचिन्हित पूर्णांक inlen;
	अचिन्हित पूर्णांक outlen;
	अचिन्हित अक्षर data[];
पूर्ण Scsi_Ioctl_Command;

प्रकार काष्ठा scsi_idlun अणु
	__u32 dev_id;
	__u32 host_unique_id;
पूर्ण Scsi_Idlun;

/* Fibre Channel WWN, port_id काष्ठा */
प्रकार काष्ठा scsi_fctargaddress अणु
	__u32 host_port_id;
	अचिन्हित अक्षर host_wwn[8]; // include शून्य term.
पूर्ण Scsi_FCTargAddress;

पूर्णांक scsi_ioctl_block_when_processing_errors(काष्ठा scsi_device *sdev,
		पूर्णांक cmd, bool ndelay);
बाह्य पूर्णांक scsi_ioctl(काष्ठा scsi_device *, पूर्णांक, व्योम __user *);
बाह्य पूर्णांक scsi_compat_ioctl(काष्ठा scsi_device *sdev, पूर्णांक cmd, व्योम __user *arg);

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _SCSI_IOCTL_H */
