<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 *  Copyright (C) 2005 Mike Isely <isely@pobox.com>
 *  Copyright (C) 2004 Aurelien Alleaume <slts@मुक्त.fr>
 */

#समावेश <linux/slab.h>
#समावेश "pvrusb2-eeprom.h"
#समावेश "pvrusb2-hdw-internal.h"
#समावेश "pvrusb2-debug.h"

#घोषणा trace_eeprom(...) pvr2_trace(PVR2_TRACE_EEPROM,__VA_ARGS__)



/*

   Read and analyze data in the eeprom.  Use tveeprom to figure out
   the packet काष्ठाure, since this is another Hauppauge device and
   पूर्णांकernally it has a family resemblance to ivtv-type devices

*/

#समावेश <media/tveeprom.h>

/* We seem to only be पूर्णांकerested in the last 128 bytes of the EEPROM */
#घोषणा EEPROM_SIZE 128

/* Grab EEPROM contents, needed क्रम direct method. */
अटल u8 *pvr2_eeprom_fetch(काष्ठा pvr2_hdw *hdw)
अणु
	काष्ठा i2c_msg msg[2];
	u8 *eeprom;
	u8 iadd[2];
	u8 addr;
	u16 eepromSize;
	अचिन्हित पूर्णांक offs;
	पूर्णांक ret;
	पूर्णांक mode16 = 0;
	अचिन्हित pcnt,tcnt;
	eeprom = kzalloc(EEPROM_SIZE, GFP_KERNEL);
	अगर (!eeprom) अणु
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "Failed to allocate memory required to read eeprom");
		वापस शून्य;
	पूर्ण

	trace_eeprom("Value for eeprom addr from controller was 0x%x",
		     hdw->eeprom_addr);
	addr = hdw->eeprom_addr;
	/* Seems that अगर the high bit is set, then the *real* eeprom
	   address is shअगरted right now bit position (noticed this in
	   newer PVR USB2 hardware) */
	अगर (addr & 0x80) addr >>= 1;

	/* FX2 करोcumentation states that a 16bit-addressed eeprom is
	   expected अगर the I2C address is an odd number (yeah, this is
	   strange but it's what they करो) */
	mode16 = (addr & 1);
	eepromSize = (mode16 ? 4096 : 256);
	trace_eeprom("Examining %d byte eeprom at location 0x%x using %d bit addressing",
		     eepromSize, addr,
		     mode16 ? 16 : 8);

	msg[0].addr = addr;
	msg[0].flags = 0;
	msg[0].len = mode16 ? 2 : 1;
	msg[0].buf = iadd;
	msg[1].addr = addr;
	msg[1].flags = I2C_M_RD;

	/* We have to करो the actual eeprom data fetch ourselves, because
	   (1) we're only fetching part of the eeprom, and (2) अगर we were
	   getting the whole thing our I2C driver can't grab it in one
	   pass - which is what tveeprom is otherwise going to attempt */
	क्रम (tcnt = 0; tcnt < EEPROM_SIZE; tcnt += pcnt) अणु
		pcnt = 16;
		अगर (pcnt + tcnt > EEPROM_SIZE) pcnt = EEPROM_SIZE-tcnt;
		offs = tcnt + (eepromSize - EEPROM_SIZE);
		अगर (mode16) अणु
			iadd[0] = offs >> 8;
			iadd[1] = offs;
		पूर्ण अन्यथा अणु
			iadd[0] = offs;
		पूर्ण
		msg[1].len = pcnt;
		msg[1].buf = eeprom+tcnt;
		अगर ((ret = i2c_transfer(&hdw->i2c_adap,
					msg,ARRAY_SIZE(msg))) != 2) अणु
			pvr2_trace(PVR2_TRACE_ERROR_LEGS,
				   "eeprom fetch set offs err=%d",ret);
			kमुक्त(eeprom);
			वापस शून्य;
		पूर्ण
	पूर्ण
	वापस eeprom;
पूर्ण


/* Directly call eeprom analysis function within tveeprom. */
पूर्णांक pvr2_eeprom_analyze(काष्ठा pvr2_hdw *hdw)
अणु
	u8 *eeprom;
	काष्ठा tveeprom tvdata;

	स_रखो(&tvdata,0,माप(tvdata));

	eeprom = pvr2_eeprom_fetch(hdw);
	अगर (!eeprom)
		वापस -EINVAL;

	tveeprom_hauppauge_analog(&tvdata, eeprom);

	trace_eeprom("eeprom assumed v4l tveeprom module");
	trace_eeprom("eeprom direct call results:");
	trace_eeprom("has_radio=%d",tvdata.has_radio);
	trace_eeprom("tuner_type=%d",tvdata.tuner_type);
	trace_eeprom("tuner_formats=0x%x",tvdata.tuner_क्रमmats);
	trace_eeprom("audio_processor=%d",tvdata.audio_processor);
	trace_eeprom("model=%d",tvdata.model);
	trace_eeprom("revision=%d",tvdata.revision);
	trace_eeprom("serial_number=%d",tvdata.serial_number);
	trace_eeprom("rev_str=%s",tvdata.rev_str);
	hdw->tuner_type = tvdata.tuner_type;
	hdw->tuner_updated = !0;
	hdw->serial_number = tvdata.serial_number;
	hdw->std_mask_eeprom = tvdata.tuner_क्रमmats;

	kमुक्त(eeprom);

	वापस 0;
पूर्ण
