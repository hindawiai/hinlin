<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Driver क्रम USB Mass Storage compliant devices
 * Main Header File
 *
 * Current development and मुख्यtenance by:
 *   (c) 1999-2002 Matthew Dharm (mdharm-usb@one-eyed-alien.net)
 *
 * Initial work by:
 *   (c) 1999 Michael Gee (michael@linuxspecअगरic.com)
 *
 * This driver is based on the 'USB Mass Storage Class' करोcument. This
 * describes in detail the protocol used to communicate with such
 * devices.  Clearly, the designers had SCSI and ATAPI commands in
 * mind when they created this करोcument.  The commands are all very
 * similar to commands in the SCSI-II and ATAPI specअगरications.
 *
 * It is important to note that in a number of हालs this class
 * exhibits class-specअगरic exemptions from the USB specअगरication.
 * Notably the usage of NAK, STALL and ACK dअगरfers from the norm, in
 * that they are used to communicate रुको, failed and OK on commands.
 *
 * Also, क्रम certain devices, the पूर्णांकerrupt endpoपूर्णांक is used to convey
 * status of a command.
 */

#अगर_अघोषित _USB_H_
#घोषणा _USB_H_

#समावेश <linux/usb.h>
#समावेश <linux/usb_usual.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/completion.h>
#समावेश <linux/mutex.h>
#समावेश <linux/workqueue.h>
#समावेश <scsi/scsi_host.h>

काष्ठा us_data;
काष्ठा scsi_cmnd;

/*
 * Unusual device list definitions 
 */

काष्ठा us_unusual_dev अणु
	स्थिर अक्षर* venकरोrName;
	स्थिर अक्षर* productName;
	__u8  useProtocol;
	__u8  useTransport;
	पूर्णांक (*initFunction)(काष्ठा us_data *);
पूर्ण;


/* Dynamic bitflag definitions (us->dflags): used in set_bit() etc. */
#घोषणा US_FLIDX_URB_ACTIVE	0	/* current_urb is in use    */
#घोषणा US_FLIDX_SG_ACTIVE	1	/* current_sg is in use     */
#घोषणा US_FLIDX_ABORTING	2	/* पात is in progress     */
#घोषणा US_FLIDX_DISCONNECTING	3	/* disconnect in progress   */
#घोषणा US_FLIDX_RESETTING	4	/* device reset in progress */
#घोषणा US_FLIDX_TIMED_OUT	5	/* SCSI midlayer समयd out  */
#घोषणा US_FLIDX_SCAN_PENDING	6	/* scanning not yet करोne    */
#घोषणा US_FLIDX_REDO_READ10	7	/* reकरो READ(10) command    */
#घोषणा US_FLIDX_READ10_WORKED	8	/* previous READ(10) succeeded */

#घोषणा USB_STOR_STRING_LEN 32

/*
 * We provide a DMA-mapped I/O buffer क्रम use with small USB transfers.
 * It turns out that CB[I] needs a 12-byte buffer and Bulk-only needs a
 * 31-byte buffer.  But Freecom needs a 64-byte buffer, so that's the
 * size we'll allocate.
 */

#घोषणा US_IOBUF_SIZE		64	/* Size of the DMA-mapped I/O buffer */
#घोषणा US_SENSE_SIZE		18	/* Size of the स्वतःsense data buffer */

प्रकार पूर्णांक (*trans_cmnd)(काष्ठा scsi_cmnd *, काष्ठा us_data*);
प्रकार पूर्णांक (*trans_reset)(काष्ठा us_data*);
प्रकार व्योम (*proto_cmnd)(काष्ठा scsi_cmnd*, काष्ठा us_data*);
प्रकार व्योम (*extra_data_deकाष्ठाor)(व्योम *);	/* extra data deकाष्ठाor */
प्रकार व्योम (*pm_hook)(काष्ठा us_data *, पूर्णांक);	/* घातer management hook */

#घोषणा US_SUSPEND	0
#घोषणा US_RESUME	1

/* we allocate one of these क्रम every device that we remember */
काष्ठा us_data अणु
	/*
	 * The device we're working with
	 * It's important to note:
	 *    (o) you must hold dev_mutex to change pusb_dev
	 */
	काष्ठा mutex		dev_mutex;	 /* protect pusb_dev */
	काष्ठा usb_device	*pusb_dev;	 /* this usb_device */
	काष्ठा usb_पूर्णांकerface	*pusb_पूर्णांकf;	 /* this पूर्णांकerface */
	स्थिर काष्ठा us_unusual_dev   *unusual_dev;
						/* device-filter entry     */
	अचिन्हित दीर्घ		fflags;		 /* fixed flags from filter */
	अचिन्हित दीर्घ		dflags;		 /* dynamic atomic bitflags */
	अचिन्हित पूर्णांक		send_bulk_pipe;	 /* cached pipe values */
	अचिन्हित पूर्णांक		recv_bulk_pipe;
	अचिन्हित पूर्णांक		send_ctrl_pipe;
	अचिन्हित पूर्णांक		recv_ctrl_pipe;
	अचिन्हित पूर्णांक		recv_पूर्णांकr_pipe;

	/* inक्रमmation about the device */
	अक्षर			*transport_name;
	अक्षर			*protocol_name;
	__le32			bcs_signature;
	u8			subclass;
	u8			protocol;
	u8			max_lun;

	u8			अगरnum;		 /* पूर्णांकerface number   */
	u8			ep_bInterval;	 /* पूर्णांकerrupt पूर्णांकerval */

	/* function poपूर्णांकers क्रम this device */
	trans_cmnd		transport;	 /* transport function	   */
	trans_reset		transport_reset; /* transport device reset */
	proto_cmnd		proto_handler;	 /* protocol handler	   */

	/* SCSI पूर्णांकerfaces */
	काष्ठा scsi_cmnd	*srb;		 /* current srb		*/
	अचिन्हित पूर्णांक		tag;		 /* current dCBWTag	*/
	अक्षर			scsi_name[32];	 /* scsi_host name	*/

	/* control and bulk communications data */
	काष्ठा urb		*current_urb;	 /* USB requests	 */
	काष्ठा usb_ctrlrequest	*cr;		 /* control requests	 */
	काष्ठा usb_sg_request	current_sg;	 /* scatter-gather req.  */
	अचिन्हित अक्षर		*iobuf;		 /* I/O buffer		 */
	dma_addr_t		iobuf_dma;	 /* buffer DMA addresses */
	काष्ठा task_काष्ठा	*ctl_thपढ़ो;	 /* the control thपढ़ो   */

	/* mutual exclusion and synchronization काष्ठाures */
	काष्ठा completion	cmnd_पढ़ोy;	 /* to sleep thपढ़ो on	    */
	काष्ठा completion	notअगरy;		 /* thपढ़ो begin/end	    */
	रुको_queue_head_t	delay_रुको;	 /* रुको during reset	    */
	काष्ठा delayed_work	scan_dwork;	 /* क्रम async scanning      */

	/* subdriver inक्रमmation */
	व्योम			*extra;		 /* Any extra data          */
	extra_data_deकाष्ठाor	extra_deकाष्ठाor;/* extra data deकाष्ठाor   */
#अगर_घोषित CONFIG_PM
	pm_hook			suspend_resume_hook;
#पूर्ण_अगर

	/* hacks क्रम READ CAPACITY bug handling */
	पूर्णांक			use_last_sector_hacks;
	पूर्णांक			last_sector_retries;
पूर्ण;

/* Convert between us_data and the corresponding Scsi_Host */
अटल अंतरभूत काष्ठा Scsi_Host *us_to_host(काष्ठा us_data *us) अणु
	वापस container_of((व्योम *) us, काष्ठा Scsi_Host, hostdata);
पूर्ण
अटल अंतरभूत काष्ठा us_data *host_to_us(काष्ठा Scsi_Host *host) अणु
	वापस (काष्ठा us_data *) host->hostdata;
पूर्ण

/* Function to fill an inquiry response. See usb.c क्रम details */
बाह्य व्योम fill_inquiry_response(काष्ठा us_data *us,
	अचिन्हित अक्षर *data, अचिन्हित पूर्णांक data_len);

/*
 * The scsi_lock() and scsi_unlock() macros protect the sm_state and the
 * single queue element srb क्रम ग_लिखो access
 */
#घोषणा scsi_unlock(host)	spin_unlock_irq(host->host_lock)
#घोषणा scsi_lock(host)		spin_lock_irq(host->host_lock)

/* General routines provided by the usb-storage standard core */
#अगर_घोषित CONFIG_PM
बाह्य पूर्णांक usb_stor_suspend(काष्ठा usb_पूर्णांकerface *अगरace, pm_message_t message);
बाह्य पूर्णांक usb_stor_resume(काष्ठा usb_पूर्णांकerface *अगरace);
बाह्य पूर्णांक usb_stor_reset_resume(काष्ठा usb_पूर्णांकerface *अगरace);
#अन्यथा
#घोषणा usb_stor_suspend	शून्य
#घोषणा usb_stor_resume		शून्य
#घोषणा usb_stor_reset_resume	शून्य
#पूर्ण_अगर

बाह्य पूर्णांक usb_stor_pre_reset(काष्ठा usb_पूर्णांकerface *अगरace);
बाह्य पूर्णांक usb_stor_post_reset(काष्ठा usb_पूर्णांकerface *अगरace);

बाह्य पूर्णांक usb_stor_probe1(काष्ठा us_data **pus,
		काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		स्थिर काष्ठा usb_device_id *id,
		स्थिर काष्ठा us_unusual_dev *unusual_dev,
		काष्ठा scsi_host_ढाँचा *sht);
बाह्य पूर्णांक usb_stor_probe2(काष्ठा us_data *us);
बाह्य व्योम usb_stor_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf);

बाह्य व्योम usb_stor_adjust_quirks(काष्ठा usb_device *dev,
		अचिन्हित दीर्घ *fflags);

#घोषणा module_usb_stor_driver(__driver, __sht, __name) \
अटल पूर्णांक __init __driver##_init(व्योम) \
अणु \
	usb_stor_host_ढाँचा_init(&(__sht), __name, THIS_MODULE); \
	वापस usb_रेजिस्टर(&(__driver)); \
पूर्ण \
module_init(__driver##_init); \
अटल व्योम __निकास __driver##_निकास(व्योम) \
अणु \
	usb_deरेजिस्टर(&(__driver)); \
पूर्ण \
module_निकास(__driver##_निकास)

#पूर्ण_अगर
