<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Parallel port device probing code
 *
 * Authors:    Carsten Gross, carsten@sol.wohnheim.uni-ulm.de
 *             Philip Blundell <philb@gnu.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/parport.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>

अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *token;
	स्थिर अक्षर *descr;
पूर्ण classes[] = अणु
	अणु "",            "Legacy device" पूर्ण,
	अणु "PRINTER",     "Printer" पूर्ण,
	अणु "MODEM",       "Modem" पूर्ण,
	अणु "NET",         "Network device" पूर्ण,
	अणु "HDC",       	 "Hard disk" पूर्ण,
	अणु "PCMCIA",      "PCMCIA" पूर्ण,
	अणु "MEDIA",       "Multimedia device" पूर्ण,
	अणु "FDC",         "Floppy disk" पूर्ण,
	अणु "PORTS",       "Ports" पूर्ण,
	अणु "SCANNER",     "Scanner" पूर्ण,
	अणु "DIGICAM",     "Digital camera" पूर्ण,
	अणु "",            "Unknown device" पूर्ण,
	अणु "",            "Unspecified" पूर्ण,
	अणु "SCSIADAPTER", "SCSI adapter" पूर्ण,
	अणु शून्य,          शून्य पूर्ण
पूर्ण;

अटल व्योम pretty_prपूर्णांक(काष्ठा parport *port, पूर्णांक device)
अणु
	काष्ठा parport_device_info *info = &port->probe_info[device + 1];

	pr_info("%s", port->name);

	अगर (device >= 0)
		pr_cont(" (addr %d)", device);

	pr_cont(": %s", classes[info->class].descr);
	अगर (info->class)
		pr_cont(", %s %s", info->mfr, info->model);

	pr_cont("\n");
पूर्ण

अटल व्योम parse_data(काष्ठा parport *port, पूर्णांक device, अक्षर *str)
अणु
	अक्षर *txt = kदो_स्मृति(म_माप(str)+1, GFP_KERNEL);
	अक्षर *p = txt, *q;
	पूर्णांक guessed_class = PARPORT_CLASS_UNSPEC;
	काष्ठा parport_device_info *info = &port->probe_info[device + 1];

	अगर (!txt) अणु
		pr_warn("%s probe: memory squeeze\n", port->name);
		वापस;
	पूर्ण
	म_नकल(txt, str);
	जबतक (p) अणु
		अक्षर *sep;
		q = म_अक्षर(p, ';');
		अगर (q) *q = 0;
		sep = म_अक्षर(p, ':');
		अगर (sep) अणु
			अक्षर *u;
			*(sep++) = 0;
			/* Get rid of trailing blanks */
			u = sep + म_माप (sep) - 1;
			जबतक (u >= p && *u == ' ')
				*u-- = '\0';
			u = p;
			जबतक (*u) अणु
				*u = बड़े(*u);
				u++;
			पूर्ण
			अगर (!म_भेद(p, "MFG") || !म_भेद(p, "MANUFACTURER")) अणु
				kमुक्त(info->mfr);
				info->mfr = kstrdup(sep, GFP_KERNEL);
			पूर्ण अन्यथा अगर (!म_भेद(p, "MDL") || !म_भेद(p, "MODEL")) अणु
				kमुक्त(info->model);
				info->model = kstrdup(sep, GFP_KERNEL);
			पूर्ण अन्यथा अगर (!म_भेद(p, "CLS") || !म_भेद(p, "CLASS")) अणु
				पूर्णांक i;

				kमुक्त(info->class_name);
				info->class_name = kstrdup(sep, GFP_KERNEL);
				क्रम (u = sep; *u; u++)
					*u = बड़े(*u);
				क्रम (i = 0; classes[i].token; i++) अणु
					अगर (!म_भेद(classes[i].token, sep)) अणु
						info->class = i;
						जाओ rock_on;
					पूर्ण
				पूर्ण
				pr_warn("%s probe: warning, class '%s' not understood\n",
					port->name, sep);
				info->class = PARPORT_CLASS_OTHER;
			पूर्ण अन्यथा अगर (!म_भेद(p, "CMD") ||
				   !म_भेद(p, "COMMAND SET")) अणु
				kमुक्त(info->cmdset);
				info->cmdset = kstrdup(sep, GFP_KERNEL);
				/* अगर it speaks prपूर्णांकer language, it's
				   probably a prपूर्णांकer */
				अगर (म_माला(sep, "PJL") || म_माला(sep, "PCL"))
					guessed_class = PARPORT_CLASS_PRINTER;
			पूर्ण अन्यथा अगर (!म_भेद(p, "DES") || !म_भेद(p, "DESCRIPTION")) अणु
				kमुक्त(info->description);
				info->description = kstrdup(sep, GFP_KERNEL);
			पूर्ण
		पूर्ण
	rock_on:
		अगर (q)
			p = q + 1;
		अन्यथा
			p = शून्य;
	पूर्ण

	/* If the device didn't tell us its class, maybe we have managed to
	   guess one from the things it did say. */
	अगर (info->class == PARPORT_CLASS_UNSPEC)
		info->class = guessed_class;

	pretty_prपूर्णांक (port, device);

	kमुक्त(txt);
पूर्ण

/* Read up to count-1 bytes of device id. Terminate buffer with
 * '\0'. Buffer begins with two Device ID length bytes as given by
 * device. */
अटल sमाप_प्रकार parport_पढ़ो_device_id (काष्ठा parport *port, अक्षर *buffer,
				       माप_प्रकार count)
अणु
	अचिन्हित अक्षर length[2];
	अचिन्हित lelen, belen;
	माप_प्रकार idlens[4];
	अचिन्हित numidlens;
	अचिन्हित current_idlen;
	sमाप_प्रकार retval;
	माप_प्रकार len;

	/* First two bytes are MSB,LSB of inclusive length. */
	retval = parport_पढ़ो (port, length, 2);

	अगर (retval < 0)
		वापस retval;
	अगर (retval != 2)
		वापस -EIO;

	अगर (count < 2)
		वापस 0;
	स_नकल(buffer, length, 2);
	len = 2;

	/* Some devices wrongly send LE length, and some send it two
	 * bytes लघु. Conकाष्ठा a sorted array of lengths to try. */
	belen = (length[0] << 8) + length[1];
	lelen = (length[1] << 8) + length[0];
	idlens[0] = min(belen, lelen);
	idlens[1] = idlens[0]+2;
	अगर (belen != lelen) अणु
		पूर्णांक off = 2;
		/* Don't try lengths of 0x100 and 0x200 as 1 and 2 */
		अगर (idlens[0] <= 2)
			off = 0;
		idlens[off] = max(belen, lelen);
		idlens[off+1] = idlens[off]+2;
		numidlens = off+2;
	पूर्ण
	अन्यथा अणु
		/* Some devices करोn't truly implement Device ID, but
		 * just वापस स्थिरant nibble क्रमever. This catches
		 * also those हालs. */
		अगर (idlens[0] == 0 || idlens[0] > 0xFFF) अणु
			prपूर्णांकk(KERN_DEBUG "%s: reported broken Device ID length of %#zX bytes\n",
			       port->name, idlens[0]);
			वापस -EIO;
		पूर्ण
		numidlens = 2;
	पूर्ण

	/* Try to respect the given ID length despite all the bugs in
	 * the ID length. Read according to लघुest possible ID
	 * first. */
	क्रम (current_idlen = 0; current_idlen < numidlens; ++current_idlen) अणु
		माप_प्रकार idlen = idlens[current_idlen];
		अगर (idlen+1 >= count)
			अवरोध;

		retval = parport_पढ़ो (port, buffer+len, idlen-len);

		अगर (retval < 0)
			वापस retval;
		len += retval;

		अगर (port->physport->ieee1284.phase != IEEE1284_PH_HBUSY_DAVAIL) अणु
			अगर (belen != len) अणु
				prपूर्णांकk(KERN_DEBUG "%s: Device ID was %zd bytes while device told it would be %d bytes\n",
				       port->name, len, belen);
			पूर्ण
			जाओ करोne;
		पूर्ण

		/* This might end पढ़ोing the Device ID too
		 * soon. Hopefully the needed fields were alपढ़ोy in
		 * the first 256 bytes or so that we must have पढ़ो so
		 * far. */
		अगर (buffer[len-1] == ';') अणु
			prपूर्णांकk(KERN_DEBUG "%s: Device ID reading stopped before device told data not available. Current idlen %u of %u, len bytes %02X %02X\n",
			       port->name, current_idlen, numidlens,
			       length[0], length[1]);
			जाओ करोne;
		पूर्ण
	पूर्ण
	अगर (current_idlen < numidlens) अणु
		/* Buffer not large enough, पढ़ो to end of buffer. */
		माप_प्रकार idlen, len2;
		अगर (len+1 < count) अणु
			retval = parport_पढ़ो (port, buffer+len, count-len-1);
			अगर (retval < 0)
				वापस retval;
			len += retval;
		पूर्ण
		/* Read the whole ID since some devices would not
		 * otherwise give back the Device ID from beginning
		 * next समय when asked. */
		idlen = idlens[current_idlen];
		len2 = len;
		जबतक(len2 < idlen && retval > 0) अणु
			अक्षर पंचांगp[4];
			retval = parport_पढ़ो (port, पंचांगp,
					       min(माप पंचांगp, idlen-len2));
			अगर (retval < 0)
				वापस retval;
			len2 += retval;
		पूर्ण
	पूर्ण
	/* In addition, there are broken devices out there that करोn't
	   even finish off with a semi-colon. We करो not need to care
	   about those at this समय. */
 करोne:
	buffer[len] = '\0';
	वापस len;
पूर्ण

/* Get Std 1284 Device ID. */
sमाप_प्रकार parport_device_id (पूर्णांक devnum, अक्षर *buffer, माप_प्रकार count)
अणु
	sमाप_प्रकार retval = -ENXIO;
	काष्ठा pardevice *dev = parport_खोलो(devnum, daisy_dev_name);
	अगर (!dev)
		वापस -ENXIO;

	parport_claim_or_block (dev);

	/* Negotiate to compatibility mode, and then to device ID
	 * mode. (This so that we start क्रमm beginning of device ID अगर
	 * alपढ़ोy in device ID mode.) */
	parport_negotiate (dev->port, IEEE1284_MODE_COMPAT);
	retval = parport_negotiate (dev->port,
				    IEEE1284_MODE_NIBBLE | IEEE1284_DEVICEID);

	अगर (!retval) अणु
		retval = parport_पढ़ो_device_id (dev->port, buffer, count);
		parport_negotiate (dev->port, IEEE1284_MODE_COMPAT);
		अगर (retval > 2)
			parse_data (dev->port, dev->daisy, buffer+2);
	पूर्ण

	parport_release (dev);
	parport_बंद (dev);
	वापस retval;
पूर्ण
