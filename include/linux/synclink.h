<शैली गुरु>
/*
 * SyncLink Multiprotocol Serial Adapter Driver
 *
 * $Id: synclink.h,v 3.14 2006/07/17 20:15:43 paulkf Exp $
 *
 * Copyright (C) 1998-2000 by Microgate Corporation
 *
 * Redistribution of this file is permitted under
 * the terms of the GNU Public License (GPL)
 */
#अगर_अघोषित _SYNCLINK_H_
#घोषणा _SYNCLINK_H_

#समावेश <uapi/linux/synclink.h>

/* provide 32 bit ioctl compatibility on 64 bit प्रणालीs */
#अगर_घोषित CONFIG_COMPAT
#समावेश <linux/compat.h>
काष्ठा MGSL_PARAMS32 अणु
	compat_uदीर्घ_t	mode;
	अचिन्हित अक्षर	loopback;
	अचिन्हित लघु	flags;
	अचिन्हित अक्षर	encoding;
	compat_uदीर्घ_t	घड़ी_speed;
	अचिन्हित अक्षर	addr_filter;
	अचिन्हित लघु	crc_type;
	अचिन्हित अक्षर	preamble_length;
	अचिन्हित अक्षर	preamble;
	compat_uदीर्घ_t	data_rate;
	अचिन्हित अक्षर	data_bits;
	अचिन्हित अक्षर	stop_bits;
	अचिन्हित अक्षर	parity;
पूर्ण;
#घोषणा MGSL_IOCSPARAMS32 _IOW(MGSL_MAGIC_IOC,0,काष्ठा MGSL_PARAMS32)
#घोषणा MGSL_IOCGPARAMS32 _IOR(MGSL_MAGIC_IOC,1,काष्ठा MGSL_PARAMS32)
#पूर्ण_अगर
#पूर्ण_अगर /* _SYNCLINK_H_ */
