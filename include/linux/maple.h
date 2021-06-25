<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_MAPLE_H
#घोषणा __LINUX_MAPLE_H

#समावेश <mach/maple.h>

काष्ठा device;
बाह्य काष्ठा bus_type maple_bus_type;

/* Maple Bus command and response codes */
क्रमागत maple_code अणु
	MAPLE_RESPONSE_खाताERR =	-5,
	MAPLE_RESPONSE_AGAIN,	/* retransmit */
	MAPLE_RESPONSE_BADCMD,
	MAPLE_RESPONSE_BADFUNC,
	MAPLE_RESPONSE_NONE,	/* unit didn't respond*/
	MAPLE_COMMAND_DEVINFO =		1,
	MAPLE_COMMAND_ALLINFO,
	MAPLE_COMMAND_RESET,
	MAPLE_COMMAND_KILL,
	MAPLE_RESPONSE_DEVINFO,
	MAPLE_RESPONSE_ALLINFO,
	MAPLE_RESPONSE_OK,
	MAPLE_RESPONSE_DATATRF,
	MAPLE_COMMAND_GETCOND,
	MAPLE_COMMAND_GETMINFO,
	MAPLE_COMMAND_BREAD,
	MAPLE_COMMAND_BWRITE,
	MAPLE_COMMAND_BSYNC,
	MAPLE_COMMAND_SETCOND,
	MAPLE_COMMAND_MICCONTROL
पूर्ण;

क्रमागत maple_file_errors अणु
	MAPLE_खाताERR_INVALID_PARTITION =	0x01000000,
	MAPLE_खाताERR_PHASE_ERROR =		0x02000000,
	MAPLE_खाताERR_INVALID_BLOCK =		0x04000000,
	MAPLE_खाताERR_WRITE_ERROR =		0x08000000,
	MAPLE_खाताERR_INVALID_WRITE_LENGTH =	0x10000000,
	MAPLE_खाताERR_BAD_CRC = 		0x20000000
पूर्ण;

काष्ठा maple_buffer अणु
	अक्षर bufx[0x400];
	व्योम *buf;
पूर्ण;

काष्ठा mapleq अणु
	काष्ठा list_head list;
	काष्ठा maple_device *dev;
	काष्ठा maple_buffer *recvbuf;
	व्योम *sendbuf, *recvbuf_p2;
	अचिन्हित अक्षर length;
	क्रमागत maple_code command;
पूर्ण;

काष्ठा maple_devinfo अणु
	अचिन्हित दीर्घ function;
	अचिन्हित दीर्घ function_data[3];
	अचिन्हित अक्षर area_code;
	अचिन्हित अक्षर connector_direction;
	अक्षर product_name[31];
	अक्षर product_licence[61];
	अचिन्हित लघु standby_घातer;
	अचिन्हित लघु max_घातer;
पूर्ण;

काष्ठा maple_device अणु
	काष्ठा maple_driver *driver;
	काष्ठा mapleq *mq;
	व्योम (*callback) (काष्ठा mapleq * mq);
	व्योम (*fileerr_handler)(काष्ठा maple_device *mdev, व्योम *recvbuf);
	पूर्णांक (*can_unload)(काष्ठा maple_device *mdev);
	अचिन्हित दीर्घ when, पूर्णांकerval, function;
	काष्ठा maple_devinfo devinfo;
	अचिन्हित अक्षर port, unit;
	अक्षर product_name[32];
	अक्षर product_licence[64];
	atomic_t busy;
	रुको_queue_head_t maple_रुको;
	काष्ठा device dev;
पूर्ण;

काष्ठा maple_driver अणु
	अचिन्हित दीर्घ function;
	काष्ठा device_driver drv;
पूर्ण;

व्योम maple_अ_लोond_callback(काष्ठा maple_device *dev,
			    व्योम (*callback) (काष्ठा mapleq * mq),
			    अचिन्हित दीर्घ पूर्णांकerval,
			    अचिन्हित दीर्घ function);
पूर्णांक maple_driver_रेजिस्टर(काष्ठा maple_driver *);
व्योम maple_driver_unरेजिस्टर(काष्ठा maple_driver *);

पूर्णांक maple_add_packet(काष्ठा maple_device *mdev, u32 function,
	u32 command, u32 length, व्योम *data);
व्योम maple_clear_dev(काष्ठा maple_device *mdev);

#घोषणा to_maple_dev(n) container_of(n, काष्ठा maple_device, dev)
#घोषणा to_maple_driver(n) container_of(n, काष्ठा maple_driver, drv)

#घोषणा maple_get_drvdata(d)		dev_get_drvdata(&(d)->dev)
#घोषणा maple_set_drvdata(d,p)		dev_set_drvdata(&(d)->dev, (p))

#पूर्ण_अगर				/* __LINUX_MAPLE_H */
