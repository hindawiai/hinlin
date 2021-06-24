<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* SMBUS message transfer tracepoपूर्णांकs
 *
 * Copyright (C) 2013 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM smbus

#अगर !defined(_TRACE_SMBUS_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_SMBUS_H

#समावेश <linux/i2c.h>
#समावेश <linux/tracepoपूर्णांक.h>

/*
 * drivers/i2c/i2c-core-smbus.c
 */

/*
 * i2c_smbus_xfer() ग_लिखो data or procedure call request
 */
TRACE_EVENT_CONDITION(smbus_ग_लिखो,
	TP_PROTO(स्थिर काष्ठा i2c_adapter *adap,
		 u16 addr, अचिन्हित लघु flags,
		 अक्षर पढ़ो_ग_लिखो, u8 command, पूर्णांक protocol,
		 स्थिर जोड़ i2c_smbus_data *data),
	TP_ARGS(adap, addr, flags, पढ़ो_ग_लिखो, command, protocol, data),
	TP_CONDITION(पढ़ो_ग_लिखो == I2C_SMBUS_WRITE ||
		     protocol == I2C_SMBUS_PROC_CALL ||
		     protocol == I2C_SMBUS_BLOCK_PROC_CALL),
	TP_STRUCT__entry(
		__field(पूर्णांक,	adapter_nr		)
		__field(__u16,	addr			)
		__field(__u16,	flags			)
		__field(__u8,	command			)
		__field(__u8,	len			)
		__field(__u32,	protocol		)
		__array(__u8, buf, I2C_SMBUS_BLOCK_MAX + 2)	),
	TP_fast_assign(
		__entry->adapter_nr = adap->nr;
		__entry->addr = addr;
		__entry->flags = flags;
		__entry->command = command;
		__entry->protocol = protocol;

		चयन (protocol) अणु
		हाल I2C_SMBUS_BYTE_DATA:
			__entry->len = 1;
			जाओ copy;
		हाल I2C_SMBUS_WORD_DATA:
		हाल I2C_SMBUS_PROC_CALL:
			__entry->len = 2;
			जाओ copy;
		हाल I2C_SMBUS_BLOCK_DATA:
		हाल I2C_SMBUS_BLOCK_PROC_CALL:
		हाल I2C_SMBUS_I2C_BLOCK_DATA:
			__entry->len = data->block[0] + 1;
		copy:
			स_नकल(__entry->buf, data->block, __entry->len);
			अवरोध;
		हाल I2C_SMBUS_QUICK:
		हाल I2C_SMBUS_BYTE:
		हाल I2C_SMBUS_I2C_BLOCK_BROKEN:
		शेष:
			__entry->len = 0;
		पूर्ण
		       ),
	TP_prपूर्णांकk("i2c-%d a=%03x f=%04x c=%x %s l=%u [%*phD]",
		  __entry->adapter_nr,
		  __entry->addr,
		  __entry->flags,
		  __entry->command,
		  __prपूर्णांक_symbolic(__entry->protocol,
				   अणु I2C_SMBUS_QUICK,		"QUICK"	पूर्ण,
				   अणु I2C_SMBUS_BYTE,		"BYTE"	पूर्ण,
				   अणु I2C_SMBUS_BYTE_DATA,		"BYTE_DATA" पूर्ण,
				   अणु I2C_SMBUS_WORD_DATA,		"WORD_DATA" पूर्ण,
				   अणु I2C_SMBUS_PROC_CALL,		"PROC_CALL" पूर्ण,
				   अणु I2C_SMBUS_BLOCK_DATA,		"BLOCK_DATA" पूर्ण,
				   अणु I2C_SMBUS_I2C_BLOCK_BROKEN,	"I2C_BLOCK_BROKEN" पूर्ण,
				   अणु I2C_SMBUS_BLOCK_PROC_CALL,	"BLOCK_PROC_CALL" पूर्ण,
				   अणु I2C_SMBUS_I2C_BLOCK_DATA,	"I2C_BLOCK_DATA" पूर्ण),
		  __entry->len,
		  __entry->len, __entry->buf
		  ));

/*
 * i2c_smbus_xfer() पढ़ो data request
 */
TRACE_EVENT_CONDITION(smbus_पढ़ो,
	TP_PROTO(स्थिर काष्ठा i2c_adapter *adap,
		 u16 addr, अचिन्हित लघु flags,
		 अक्षर पढ़ो_ग_लिखो, u8 command, पूर्णांक protocol),
	TP_ARGS(adap, addr, flags, पढ़ो_ग_लिखो, command, protocol),
	TP_CONDITION(!(पढ़ो_ग_लिखो == I2C_SMBUS_WRITE ||
		       protocol == I2C_SMBUS_PROC_CALL ||
		       protocol == I2C_SMBUS_BLOCK_PROC_CALL)),
	TP_STRUCT__entry(
		__field(पूर्णांक,	adapter_nr		)
		__field(__u16,	flags			)
		__field(__u16,	addr			)
		__field(__u8,	command			)
		__field(__u32,	protocol		)
		__array(__u8, buf, I2C_SMBUS_BLOCK_MAX + 2)	),
	TP_fast_assign(
		__entry->adapter_nr = adap->nr;
		__entry->addr = addr;
		__entry->flags = flags;
		__entry->command = command;
		__entry->protocol = protocol;
		       ),
	TP_prपूर्णांकk("i2c-%d a=%03x f=%04x c=%x %s",
		  __entry->adapter_nr,
		  __entry->addr,
		  __entry->flags,
		  __entry->command,
		  __prपूर्णांक_symbolic(__entry->protocol,
				   अणु I2C_SMBUS_QUICK,		"QUICK"	पूर्ण,
				   अणु I2C_SMBUS_BYTE,		"BYTE"	पूर्ण,
				   अणु I2C_SMBUS_BYTE_DATA,		"BYTE_DATA" पूर्ण,
				   अणु I2C_SMBUS_WORD_DATA,		"WORD_DATA" पूर्ण,
				   अणु I2C_SMBUS_PROC_CALL,		"PROC_CALL" पूर्ण,
				   अणु I2C_SMBUS_BLOCK_DATA,		"BLOCK_DATA" पूर्ण,
				   अणु I2C_SMBUS_I2C_BLOCK_BROKEN,	"I2C_BLOCK_BROKEN" पूर्ण,
				   अणु I2C_SMBUS_BLOCK_PROC_CALL,	"BLOCK_PROC_CALL" पूर्ण,
				   अणु I2C_SMBUS_I2C_BLOCK_DATA,	"I2C_BLOCK_DATA" पूर्ण)
		  ));

/*
 * i2c_smbus_xfer() पढ़ो data or procedure call reply
 */
TRACE_EVENT_CONDITION(smbus_reply,
	TP_PROTO(स्थिर काष्ठा i2c_adapter *adap,
		 u16 addr, अचिन्हित लघु flags,
		 अक्षर पढ़ो_ग_लिखो, u8 command, पूर्णांक protocol,
		 स्थिर जोड़ i2c_smbus_data *data, पूर्णांक res),
	TP_ARGS(adap, addr, flags, पढ़ो_ग_लिखो, command, protocol, data, res),
	TP_CONDITION(res >= 0 && पढ़ो_ग_लिखो == I2C_SMBUS_READ),
	TP_STRUCT__entry(
		__field(पूर्णांक,	adapter_nr		)
		__field(__u16,	addr			)
		__field(__u16,	flags			)
		__field(__u8,	command			)
		__field(__u8,	len			)
		__field(__u32,	protocol		)
		__array(__u8, buf, I2C_SMBUS_BLOCK_MAX + 2)	),
	TP_fast_assign(
		__entry->adapter_nr = adap->nr;
		__entry->addr = addr;
		__entry->flags = flags;
		__entry->command = command;
		__entry->protocol = protocol;

		चयन (protocol) अणु
		हाल I2C_SMBUS_BYTE:
		हाल I2C_SMBUS_BYTE_DATA:
			__entry->len = 1;
			जाओ copy;
		हाल I2C_SMBUS_WORD_DATA:
		हाल I2C_SMBUS_PROC_CALL:
			__entry->len = 2;
			जाओ copy;
		हाल I2C_SMBUS_BLOCK_DATA:
		हाल I2C_SMBUS_BLOCK_PROC_CALL:
		हाल I2C_SMBUS_I2C_BLOCK_DATA:
			__entry->len = data->block[0] + 1;
		copy:
			स_नकल(__entry->buf, data->block, __entry->len);
			अवरोध;
		हाल I2C_SMBUS_QUICK:
		हाल I2C_SMBUS_I2C_BLOCK_BROKEN:
		शेष:
			__entry->len = 0;
		पूर्ण
		       ),
	TP_prपूर्णांकk("i2c-%d a=%03x f=%04x c=%x %s l=%u [%*phD]",
		  __entry->adapter_nr,
		  __entry->addr,
		  __entry->flags,
		  __entry->command,
		  __prपूर्णांक_symbolic(__entry->protocol,
				   अणु I2C_SMBUS_QUICK,		"QUICK"	पूर्ण,
				   अणु I2C_SMBUS_BYTE,		"BYTE"	पूर्ण,
				   अणु I2C_SMBUS_BYTE_DATA,		"BYTE_DATA" पूर्ण,
				   अणु I2C_SMBUS_WORD_DATA,		"WORD_DATA" पूर्ण,
				   अणु I2C_SMBUS_PROC_CALL,		"PROC_CALL" पूर्ण,
				   अणु I2C_SMBUS_BLOCK_DATA,		"BLOCK_DATA" पूर्ण,
				   अणु I2C_SMBUS_I2C_BLOCK_BROKEN,	"I2C_BLOCK_BROKEN" पूर्ण,
				   अणु I2C_SMBUS_BLOCK_PROC_CALL,	"BLOCK_PROC_CALL" पूर्ण,
				   अणु I2C_SMBUS_I2C_BLOCK_DATA,	"I2C_BLOCK_DATA" पूर्ण),
		  __entry->len,
		  __entry->len, __entry->buf
		  ));

/*
 * i2c_smbus_xfer() result
 */
TRACE_EVENT(smbus_result,
	    TP_PROTO(स्थिर काष्ठा i2c_adapter *adap,
		     u16 addr, अचिन्हित लघु flags,
		     अक्षर पढ़ो_ग_लिखो, u8 command, पूर्णांक protocol,
		     पूर्णांक res),
	    TP_ARGS(adap, addr, flags, पढ़ो_ग_लिखो, command, protocol, res),
	    TP_STRUCT__entry(
		    __field(पूर्णांक,	adapter_nr		)
		    __field(__u16,	addr			)
		    __field(__u16,	flags			)
		    __field(__u8,	पढ़ो_ग_लिखो		)
		    __field(__u8,	command			)
		    __field(__s16,	res			)
		    __field(__u32,	protocol		)
			     ),
	    TP_fast_assign(
		    __entry->adapter_nr = adap->nr;
		    __entry->addr = addr;
		    __entry->flags = flags;
		    __entry->पढ़ो_ग_लिखो = पढ़ो_ग_लिखो;
		    __entry->command = command;
		    __entry->protocol = protocol;
		    __entry->res = res;
			   ),
	    TP_prपूर्णांकk("i2c-%d a=%03x f=%04x c=%x %s %s res=%d",
		      __entry->adapter_nr,
		      __entry->addr,
		      __entry->flags,
		      __entry->command,
		      __prपूर्णांक_symbolic(__entry->protocol,
				       अणु I2C_SMBUS_QUICK,		"QUICK"	पूर्ण,
				       अणु I2C_SMBUS_BYTE,		"BYTE"	पूर्ण,
				       अणु I2C_SMBUS_BYTE_DATA,		"BYTE_DATA" पूर्ण,
				       अणु I2C_SMBUS_WORD_DATA,		"WORD_DATA" पूर्ण,
				       अणु I2C_SMBUS_PROC_CALL,		"PROC_CALL" पूर्ण,
				       अणु I2C_SMBUS_BLOCK_DATA,		"BLOCK_DATA" पूर्ण,
				       अणु I2C_SMBUS_I2C_BLOCK_BROKEN,	"I2C_BLOCK_BROKEN" पूर्ण,
				       अणु I2C_SMBUS_BLOCK_PROC_CALL,	"BLOCK_PROC_CALL" पूर्ण,
				       अणु I2C_SMBUS_I2C_BLOCK_DATA,	"I2C_BLOCK_DATA" पूर्ण),
		      __entry->पढ़ो_ग_लिखो == I2C_SMBUS_WRITE ? "wr" : "rd",
		      __entry->res
		      ));

#पूर्ण_अगर /* _TRACE_SMBUS_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
