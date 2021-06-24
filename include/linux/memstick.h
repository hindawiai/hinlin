<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Sony MemoryStick support
 *
 *  Copyright (C) 2007 Alex Dubov <oakad@yahoo.com>
 */

#अगर_अघोषित _MEMSTICK_H
#घोषणा _MEMSTICK_H

#समावेश <linux/workqueue.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/device.h>

/*** Hardware based काष्ठाures ***/

काष्ठा ms_status_रेजिस्टर अणु
	अचिन्हित अक्षर reserved;
	अचिन्हित अक्षर पूर्णांकerrupt;
#घोषणा MEMSTICK_INT_CMDNAK 0x01
#घोषणा MEMSTICK_INT_IOREQ  0x08
#घोषणा MEMSTICK_INT_IOBREQ 0x10
#घोषणा MEMSTICK_INT_BREQ   0x20
#घोषणा MEMSTICK_INT_ERR    0x40
#घोषणा MEMSTICK_INT_CED    0x80

	अचिन्हित अक्षर status0;
#घोषणा MEMSTICK_STATUS0_WP  0x01
#घोषणा MEMSTICK_STATUS0_SL  0x02
#घोषणा MEMSTICK_STATUS0_BF  0x10
#घोषणा MEMSTICK_STATUS0_BE  0x20
#घोषणा MEMSTICK_STATUS0_FB0 0x40
#घोषणा MEMSTICK_STATUS0_MB  0x80

	अचिन्हित अक्षर status1;
#घोषणा MEMSTICK_STATUS1_UCFG 0x01
#घोषणा MEMSTICK_STATUS1_FGER 0x02
#घोषणा MEMSTICK_STATUS1_UCEX 0x04
#घोषणा MEMSTICK_STATUS1_EXER 0x08
#घोषणा MEMSTICK_STATUS1_UCDT 0x10
#घोषणा MEMSTICK_STATUS1_DTER 0x20
#घोषणा MEMSTICK_STATUS1_FB1  0x40
#घोषणा MEMSTICK_STATUS1_MB   0x80
पूर्ण __attribute__((packed));

काष्ठा ms_id_रेजिस्टर अणु
	अचिन्हित अक्षर type;
	अचिन्हित अक्षर अगर_mode;
	अचिन्हित अक्षर category;
	अचिन्हित अक्षर class;
पूर्ण __attribute__((packed));

काष्ठा ms_param_रेजिस्टर अणु
	अचिन्हित अक्षर प्रणाली;
#घोषणा MEMSTICK_SYS_PAM  0x08
#घोषणा MEMSTICK_SYS_BAMD 0x80

	अचिन्हित अक्षर block_address_msb;
	अचिन्हित लघु block_address;
	अचिन्हित अक्षर cp;
#घोषणा MEMSTICK_CP_BLOCK     0x00
#घोषणा MEMSTICK_CP_PAGE      0x20
#घोषणा MEMSTICK_CP_EXTRA     0x40
#घोषणा MEMSTICK_CP_OVERWRITE 0x80

	अचिन्हित अक्षर page_address;
पूर्ण __attribute__((packed));

काष्ठा ms_extra_data_रेजिस्टर अणु
	अचिन्हित अक्षर  overग_लिखो_flag;
#घोषणा MEMSTICK_OVERWRITE_UDST  0x10
#घोषणा MEMSTICK_OVERWRITE_PGST1 0x20
#घोषणा MEMSTICK_OVERWRITE_PGST0 0x40
#घोषणा MEMSTICK_OVERWRITE_BKST  0x80

	अचिन्हित अक्षर  management_flag;
#घोषणा MEMSTICK_MANAGEMENT_SYSFLG 0x04
#घोषणा MEMSTICK_MANAGEMENT_ATFLG  0x08
#घोषणा MEMSTICK_MANAGEMENT_SCMS1  0x10
#घोषणा MEMSTICK_MANAGEMENT_SCMS0  0x20

	अचिन्हित लघु logical_address;
पूर्ण __attribute__((packed));

काष्ठा ms_रेजिस्टर अणु
	काष्ठा ms_status_रेजिस्टर     status;
	काष्ठा ms_id_रेजिस्टर         id;
	अचिन्हित अक्षर                 reserved[8];
	काष्ठा ms_param_रेजिस्टर      param;
	काष्ठा ms_extra_data_रेजिस्टर extra_data;
पूर्ण __attribute__((packed));

काष्ठा mspro_param_रेजिस्टर अणु
	अचिन्हित अक्षर  प्रणाली;
#घोषणा MEMSTICK_SYS_PAR4   0x00
#घोषणा MEMSTICK_SYS_PAR8   0x40
#घोषणा MEMSTICK_SYS_SERIAL 0x80

	__be16 data_count;
	__be32 data_address;
	अचिन्हित अक्षर  tpc_param;
पूर्ण __attribute__((packed));

काष्ठा mspro_io_info_रेजिस्टर अणु
	अचिन्हित अक्षर version;
	अचिन्हित अक्षर io_category;
	अचिन्हित अक्षर current_req;
	अचिन्हित अक्षर card_opt_info;
	अचिन्हित अक्षर rdy_रुको_समय;
पूर्ण __attribute__((packed));

काष्ठा mspro_io_func_रेजिस्टर अणु
	अचिन्हित अक्षर func_enable;
	अचिन्हित अक्षर func_select;
	अचिन्हित अक्षर func_पूर्णांकmask;
	अचिन्हित अक्षर transfer_mode;
पूर्ण __attribute__((packed));

काष्ठा mspro_io_cmd_रेजिस्टर अणु
	अचिन्हित लघु tpc_param;
	अचिन्हित लघु data_count;
	अचिन्हित पूर्णांक   data_address;
पूर्ण __attribute__((packed));

काष्ठा mspro_रेजिस्टर अणु
	काष्ठा ms_status_रेजिस्टर     status;
	काष्ठा ms_id_रेजिस्टर         id;
	अचिन्हित अक्षर                 reserved0[8];
	काष्ठा mspro_param_रेजिस्टर   param;
	अचिन्हित अक्षर                 reserved1[8];
	काष्ठा mspro_io_info_रेजिस्टर io_info;
	काष्ठा mspro_io_func_रेजिस्टर io_func;
	अचिन्हित अक्षर                 reserved2[7];
	काष्ठा mspro_io_cmd_रेजिस्टर  io_cmd;
	अचिन्हित अक्षर                 io_पूर्णांक;
	अचिन्हित अक्षर                 io_पूर्णांक_func;
पूर्ण __attribute__((packed));

काष्ठा ms_रेजिस्टर_addr अणु
	अचिन्हित अक्षर r_offset;
	अचिन्हित अक्षर r_length;
	अचिन्हित अक्षर w_offset;
	अचिन्हित अक्षर w_length;
पूर्ण __attribute__((packed));

क्रमागत memstick_tpc अणु
	MS_TPC_READ_MG_STATUS   = 0x01,
	MS_TPC_READ_LONG_DATA   = 0x02,
	MS_TPC_READ_SHORT_DATA  = 0x03,
	MS_TPC_READ_MG_DATA     = 0x03,
	MS_TPC_READ_REG         = 0x04,
	MS_TPC_READ_QUAD_DATA   = 0x05,
	MS_TPC_READ_IO_DATA     = 0x05,
	MS_TPC_GET_INT          = 0x07,
	MS_TPC_SET_RW_REG_ADRS  = 0x08,
	MS_TPC_EX_SET_CMD       = 0x09,
	MS_TPC_WRITE_QUAD_DATA  = 0x0a,
	MS_TPC_WRITE_IO_DATA    = 0x0a,
	MS_TPC_WRITE_REG        = 0x0b,
	MS_TPC_WRITE_SHORT_DATA = 0x0c,
	MS_TPC_WRITE_MG_DATA    = 0x0c,
	MS_TPC_WRITE_LONG_DATA  = 0x0d,
	MS_TPC_SET_CMD          = 0x0e
पूर्ण;

क्रमागत memstick_command अणु
	MS_CMD_BLOCK_END       = 0x33,
	MS_CMD_RESET           = 0x3c,
	MS_CMD_BLOCK_WRITE     = 0x55,
	MS_CMD_SLEEP           = 0x5a,
	MS_CMD_BLOCK_ERASE     = 0x99,
	MS_CMD_BLOCK_READ      = 0xaa,
	MS_CMD_CLEAR_BUF       = 0xc3,
	MS_CMD_FLASH_STOP      = 0xcc,
	MS_CMD_LOAD_ID         = 0x60,
	MS_CMD_CMP_ICV         = 0x7f,
	MSPRO_CMD_FORMAT       = 0x10,
	MSPRO_CMD_SLEEP        = 0x11,
	MSPRO_CMD_WAKEUP       = 0x12,
	MSPRO_CMD_READ_DATA    = 0x20,
	MSPRO_CMD_WRITE_DATA   = 0x21,
	MSPRO_CMD_READ_ATRB    = 0x24,
	MSPRO_CMD_STOP         = 0x25,
	MSPRO_CMD_ERASE        = 0x26,
	MSPRO_CMD_READ_QUAD    = 0x27,
	MSPRO_CMD_WRITE_QUAD   = 0x28,
	MSPRO_CMD_SET_IBD      = 0x46,
	MSPRO_CMD_GET_IBD      = 0x47,
	MSPRO_CMD_IN_IO_DATA   = 0xb0,
	MSPRO_CMD_OUT_IO_DATA  = 0xb1,
	MSPRO_CMD_READ_IO_ATRB = 0xb2,
	MSPRO_CMD_IN_IO_FIFO   = 0xb3,
	MSPRO_CMD_OUT_IO_FIFO  = 0xb4,
	MSPRO_CMD_IN_IOM       = 0xb5,
	MSPRO_CMD_OUT_IOM      = 0xb6,
पूर्ण;

/*** Driver काष्ठाures and functions ***/

क्रमागत memstick_param अणु MEMSTICK_POWER = 1, MEMSTICK_INTERFACE पूर्ण;

#घोषणा MEMSTICK_POWER_OFF 0
#घोषणा MEMSTICK_POWER_ON  1

#घोषणा MEMSTICK_SERIAL   0
#घोषणा MEMSTICK_PAR4     1
#घोषणा MEMSTICK_PAR8     2

काष्ठा memstick_host;
काष्ठा memstick_driver;

काष्ठा memstick_device_id अणु
	अचिन्हित अक्षर match_flags;
#घोषणा MEMSTICK_MATCH_ALL            0x01

	अचिन्हित अक्षर type;
#घोषणा MEMSTICK_TYPE_LEGACY          0xff
#घोषणा MEMSTICK_TYPE_DUO             0x00
#घोषणा MEMSTICK_TYPE_PRO             0x01

	अचिन्हित अक्षर category;
#घोषणा MEMSTICK_CATEGORY_STORAGE     0xff
#घोषणा MEMSTICK_CATEGORY_STORAGE_DUO 0x00
#घोषणा MEMSTICK_CATEGORY_IO          0x01
#घोषणा MEMSTICK_CATEGORY_IO_PRO      0x10

	अचिन्हित अक्षर class;
#घोषणा MEMSTICK_CLASS_FLASH          0xff
#घोषणा MEMSTICK_CLASS_DUO            0x00
#घोषणा MEMSTICK_CLASS_ROM            0x01
#घोषणा MEMSTICK_CLASS_RO             0x02
#घोषणा MEMSTICK_CLASS_WP             0x03
पूर्ण;

काष्ठा memstick_request अणु
	अचिन्हित अक्षर tpc;
	अचिन्हित अक्षर data_dir:1,
		      need_card_पूर्णांक:1,
		      दीर्घ_data:1;
	अचिन्हित अक्षर पूर्णांक_reg;
	पूर्णांक           error;
	जोड़ अणु
		काष्ठा scatterlist sg;
		काष्ठा अणु
			अचिन्हित अक्षर data_len;
			अचिन्हित अक्षर data[15];
		पूर्ण;
	पूर्ण;
पूर्ण;

काष्ठा memstick_dev अणु
	काष्ठा memstick_device_id id;
	काष्ठा memstick_host     *host;
	काष्ठा ms_रेजिस्टर_addr  reg_addr;
	काष्ठा completion        mrq_complete;
	काष्ठा memstick_request  current_mrq;

	/* Check that media driver is still willing to operate the device. */
	पूर्णांक                      (*check)(काष्ठा memstick_dev *card);
	/* Get next request from the media driver.                         */
	पूर्णांक                      (*next_request)(काष्ठा memstick_dev *card,
						 काष्ठा memstick_request **mrq);
	/* Tell the media driver to stop करोing things                      */
	व्योम                     (*stop)(काष्ठा memstick_dev *card);
	/* Allow the media driver to जारी                              */
	व्योम                     (*start)(काष्ठा memstick_dev *card);

	काष्ठा device            dev;
पूर्ण;

काष्ठा memstick_host अणु
	काष्ठा mutex        lock;
	अचिन्हित पूर्णांक        id;
	अचिन्हित पूर्णांक        caps;
#घोषणा MEMSTICK_CAP_AUTO_GET_INT  1
#घोषणा MEMSTICK_CAP_PAR4          2
#घोषणा MEMSTICK_CAP_PAR8          4

	काष्ठा work_काष्ठा  media_checker;
	काष्ठा device       dev;

	काष्ठा memstick_dev *card;
	अचिन्हित पूर्णांक        retries;
	bool removing;

	/* Notअगरy the host that some requests are pending. */
	व्योम                (*request)(काष्ठा memstick_host *host);
	/* Set host IO parameters (घातer, घड़ी, etc).     */
	पूर्णांक                 (*set_param)(काष्ठा memstick_host *host,
					 क्रमागत memstick_param param,
					 पूर्णांक value);
	अचिन्हित दीर्घ       निजी[] ____cacheline_aligned;
पूर्ण;

काष्ठा memstick_driver अणु
	काष्ठा memstick_device_id *id_table;
	पूर्णांक                       (*probe)(काष्ठा memstick_dev *card);
	व्योम                      (*हटाओ)(काष्ठा memstick_dev *card);
	पूर्णांक                       (*suspend)(काष्ठा memstick_dev *card,
					     pm_message_t state);
	पूर्णांक                       (*resume)(काष्ठा memstick_dev *card);

	काष्ठा device_driver      driver;
पूर्ण;

पूर्णांक memstick_रेजिस्टर_driver(काष्ठा memstick_driver *drv);
व्योम memstick_unरेजिस्टर_driver(काष्ठा memstick_driver *drv);

काष्ठा memstick_host *memstick_alloc_host(अचिन्हित पूर्णांक extra,
					  काष्ठा device *dev);

पूर्णांक memstick_add_host(काष्ठा memstick_host *host);
व्योम memstick_हटाओ_host(काष्ठा memstick_host *host);
व्योम memstick_मुक्त_host(काष्ठा memstick_host *host);
व्योम memstick_detect_change(काष्ठा memstick_host *host);
व्योम memstick_suspend_host(काष्ठा memstick_host *host);
व्योम memstick_resume_host(काष्ठा memstick_host *host);

व्योम memstick_init_req_sg(काष्ठा memstick_request *mrq, अचिन्हित अक्षर tpc,
			  स्थिर काष्ठा scatterlist *sg);
व्योम memstick_init_req(काष्ठा memstick_request *mrq, अचिन्हित अक्षर tpc,
		       स्थिर व्योम *buf, माप_प्रकार length);
पूर्णांक memstick_next_req(काष्ठा memstick_host *host,
		      काष्ठा memstick_request **mrq);
व्योम memstick_new_req(काष्ठा memstick_host *host);

पूर्णांक memstick_set_rw_addr(काष्ठा memstick_dev *card);

अटल अंतरभूत व्योम *memstick_priv(काष्ठा memstick_host *host)
अणु
	वापस (व्योम *)host->निजी;
पूर्ण

अटल अंतरभूत व्योम *memstick_get_drvdata(काष्ठा memstick_dev *card)
अणु
	वापस dev_get_drvdata(&card->dev);
पूर्ण

अटल अंतरभूत व्योम memstick_set_drvdata(काष्ठा memstick_dev *card, व्योम *data)
अणु
	dev_set_drvdata(&card->dev, data);
पूर्ण

#पूर्ण_अगर
