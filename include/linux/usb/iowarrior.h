<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_USB_IOWARRIOR_H
#घोषणा __LINUX_USB_IOWARRIOR_H

#घोषणा CODEMERCS_MAGIC_NUMBER	0xC0	/* like COde Mercenaries */

/* Define the ioctl commands क्रम पढ़ोing and writing data */
#घोषणा IOW_WRITE	_IOW(CODEMERCS_MAGIC_NUMBER, 1, __u8 *)
#घोषणा IOW_READ	_IOW(CODEMERCS_MAGIC_NUMBER, 2, __u8 *)

/*
   A काष्ठा क्रम available device info which is पढ़ो
   with the ioctl IOW_GETINFO.
   To be compatible with 2.4 userspace which didn't have an easy way to get
   this inक्रमmation.
*/
काष्ठा iowarrior_info अणु
	/* venकरोr id : supposed to be USB_VENDOR_ID_CODEMERCS in all हालs */
	__u32 venकरोr;
	/* product id : depends on type of chip (USB_DEVICE_ID_CODEMERCS_X) */
	__u32 product;
	/* the serial number of our chip (अगर a serial-number is not available
	 * this is empty string) */
	__u8 serial[9];
	/* revision number of the chip */
	__u32 revision;
	/* USB-speed of the device (0=UNKNOWN, 1=LOW, 2=FULL 3=HIGH) */
	__u32 speed;
	/* घातer consumption of the device in mA */
	__u32 घातer;
	/* the number of the endpoपूर्णांक */
	__u32 अगर_num;
	/* size of the data-packets on this पूर्णांकerface */
	__u32 report_size;
पूर्ण;

/*
  Get some device-inक्रमmation (product-id , serial-number etc.)
  in order to identअगरy a chip.
*/
#घोषणा IOW_GETINFO _IOR(CODEMERCS_MAGIC_NUMBER, 3, काष्ठा iowarrior_info)

#पूर्ण_अगर /* __LINUX_USB_IOWARRIOR_H */
