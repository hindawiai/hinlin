<शैली गुरु>
/* Simple code to turn various tables in an ELF file पूर्णांकo alias definitions.
 * This deals with kernel dataकाष्ठाures where they should be
 * dealt with: in the kernel source.
 *
 * Copyright 2002-2003  Rusty Russell, IBM Corporation
 *           2003       Kai Germaschewski
 *
 *
 * This software may be used and distributed according to the terms
 * of the GNU General Public License, incorporated herein by reference.
 */

#समावेश "modpost.h"
#समावेश "devicetable-offsets.h"

/* We use the ELF प्रकारs क्रम kernel_uदीर्घ_t but bite the bullet and
 * use either मानक_निवेशt.h or पूर्णांकtypes.h क्रम the rest. */
#अगर KERNEL_ELFCLASS == ELFCLASS32
प्रकार Elf32_Addr	kernel_uदीर्घ_t;
#घोषणा BITS_PER_LONG 32
#अन्यथा
प्रकार Elf64_Addr	kernel_uदीर्घ_t;
#घोषणा BITS_PER_LONG 64
#पूर्ण_अगर
#अगर_घोषित __sun__
#समावेश <पूर्णांकtypes.h>
#अन्यथा
#समावेश <मानक_निवेशt.h>
#पूर्ण_अगर

#समावेश <प्रकार.स>
#समावेश <stdbool.h>

प्रकार uपूर्णांक32_t	__u32;
प्रकार uपूर्णांक16_t	__u16;
प्रकार अचिन्हित अक्षर	__u8;
प्रकार काष्ठा अणु
	__u8 b[16];
पूर्ण guid_t;

/* backwards compatibility, करोn't use in new code */
प्रकार काष्ठा अणु
	__u8 b[16];
पूर्ण uuid_le;
प्रकार काष्ठा अणु
	__u8 b[16];
पूर्ण uuid_t;
#घोषणा	UUID_STRING_LEN		36

/* Big exception to the "करोn't include kernel headers पूर्णांकo userspace, which
 * even potentially has dअगरferent endianness and word sizes, since
 * we handle those dअगरferences explicitly below */
#समावेश "../../include/linux/mod_devicetable.h"

/* This array collects all instances that use the generic करो_table */
काष्ठा devtable अणु
	स्थिर अक्षर *device_id; /* name of table, __mod_<name>__*_device_table. */
	अचिन्हित दीर्घ id_size;
	पूर्णांक (*करो_entry)(स्थिर अक्षर *filename, व्योम *symval, अक्षर *alias);
पूर्ण;

/* Size of alias provided to करो_entry functions */
#घोषणा ALIAS_SIZE 500

/* Define a variable f that holds the value of field f of काष्ठा devid
 * based at address m.
 */
#घोषणा DEF_FIELD(m, devid, f) \
	typeof(((काष्ठा devid *)0)->f) f = TO_NATIVE(*(typeof(f) *)((m) + OFF_##devid##_##f))

/* Define a variable v that holds the address of field f of काष्ठा devid
 * based at address m.  Due to the way typeof works, क्रम a field of type
 * T[N] the variable has type T(*)[N], _not_ T*.
 */
#घोषणा DEF_FIELD_ADDR_VAR(m, devid, f, v) \
	typeof(((काष्ठा devid *)0)->f) *v = ((m) + OFF_##devid##_##f)

/* Define a variable f that holds the address of field f of काष्ठा devid
 * based at address m.  Due to the way typeof works, क्रम a field of type
 * T[N] the variable has type T(*)[N], _not_ T*.
 */
#घोषणा DEF_FIELD_ADDR(m, devid, f) \
	DEF_FIELD_ADDR_VAR(m, devid, f, f)

#घोषणा ADD(str, sep, cond, field)                              \
करो अणु                                                            \
        म_जोड़ो(str, sep);                                       \
        अगर (cond)                                               \
                प्र_लिखो(str + म_माप(str),                      \
                        माप(field) == 1 ? "%02X" :           \
                        माप(field) == 2 ? "%04X" :           \
                        माप(field) == 4 ? "%08X" : "",       \
                        field);                                 \
        अन्यथा                                                    \
                प्र_लिखो(str + म_माप(str), "*");                \
पूर्ण जबतक(0)

/* End in a wildcard, क्रम future extension */
अटल अंतरभूत व्योम add_wildcard(अक्षर *str)
अणु
	पूर्णांक len = म_माप(str);

	अगर (str[len - 1] != '*')
		म_जोड़ो(str + len, "*");
पूर्ण

अटल अंतरभूत व्योम add_uuid(अक्षर *str, uuid_le uuid)
अणु
	पूर्णांक len = म_माप(str);

	प्र_लिखो(str + len, "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
		uuid.b[3], uuid.b[2], uuid.b[1], uuid.b[0],
		uuid.b[5], uuid.b[4], uuid.b[7], uuid.b[6],
		uuid.b[8], uuid.b[9], uuid.b[10], uuid.b[11],
		uuid.b[12], uuid.b[13], uuid.b[14], uuid.b[15]);
पूर्ण

/**
 * Check that माप(device_id type) are consistent with size of section
 * in .o file. If in-consistent then userspace and kernel करोes not agree
 * on actual size which is a bug.
 * Also verअगरy that the final entry in the table is all zeros.
 * Ignore both checks अगर build host dअगरfer from target host and size dअगरfers.
 **/
अटल व्योम device_id_check(स्थिर अक्षर *modname, स्थिर अक्षर *device_id,
			    अचिन्हित दीर्घ size, अचिन्हित दीर्घ id_size,
			    व्योम *symval)
अणु
	पूर्णांक i;

	अगर (size % id_size || size < id_size) अणु
		fatal("%s: sizeof(struct %s_device_id)=%lu is not a modulo "
		      "of the size of "
		      "section __mod_%s__<identifier>_device_table=%lu.\n"
		      "Fix definition of struct %s_device_id "
		      "in mod_devicetable.h\n",
		      modname, device_id, id_size, device_id, size, device_id);
	पूर्ण
	/* Verअगरy last one is a terminator */
	क्रम (i = 0; i < id_size; i++ ) अणु
		अगर (*(uपूर्णांक8_t*)(symval+size-id_size+i)) अणु
			ख_लिखो(मानक_त्रुटि,"%s: struct %s_device_id is %lu bytes.  "
				"The last of %lu is:\n",
				modname, device_id, id_size, size / id_size);
			क्रम (i = 0; i < id_size; i++ )
				ख_लिखो(मानक_त्रुटि,"0x%02x ",
					*(uपूर्णांक8_t*)(symval+size-id_size+i) );
			ख_लिखो(मानक_त्रुटि,"\n");
			fatal("%s: struct %s_device_id is not terminated "
				"with a NULL entry!\n", modname, device_id);
		पूर्ण
	पूर्ण
पूर्ण

/* USB is special because the bcdDevice can be matched against a numeric range */
/* Looks like "usb:vNpNdNdcNdscNdpNicNiscNipNinN" */
अटल व्योम करो_usb_entry(व्योम *symval,
			 अचिन्हित पूर्णांक bcdDevice_initial, पूर्णांक bcdDevice_initial_digits,
			 अचिन्हित अक्षर range_lo, अचिन्हित अक्षर range_hi,
			 अचिन्हित अक्षर max, काष्ठा module *mod)
अणु
	अक्षर alias[500];
	DEF_FIELD(symval, usb_device_id, match_flags);
	DEF_FIELD(symval, usb_device_id, idVenकरोr);
	DEF_FIELD(symval, usb_device_id, idProduct);
	DEF_FIELD(symval, usb_device_id, bcdDevice_lo);
	DEF_FIELD(symval, usb_device_id, bDeviceClass);
	DEF_FIELD(symval, usb_device_id, bDeviceSubClass);
	DEF_FIELD(symval, usb_device_id, bDeviceProtocol);
	DEF_FIELD(symval, usb_device_id, bInterfaceClass);
	DEF_FIELD(symval, usb_device_id, bInterfaceSubClass);
	DEF_FIELD(symval, usb_device_id, bInterfaceProtocol);
	DEF_FIELD(symval, usb_device_id, bInterfaceNumber);

	म_नकल(alias, "usb:");
	ADD(alias, "v", match_flags&USB_DEVICE_ID_MATCH_VENDOR,
	    idVenकरोr);
	ADD(alias, "p", match_flags&USB_DEVICE_ID_MATCH_PRODUCT,
	    idProduct);

	म_जोड़ो(alias, "d");
	अगर (bcdDevice_initial_digits)
		प्र_लिखो(alias + म_माप(alias), "%0*X",
			bcdDevice_initial_digits, bcdDevice_initial);
	अगर (range_lo == range_hi)
		प्र_लिखो(alias + म_माप(alias), "%X", range_lo);
	अन्यथा अगर (range_lo > 0 || range_hi < max) अणु
		अगर (range_lo > 0x9 || range_hi < 0xA)
			प्र_लिखो(alias + म_माप(alias),
				"[%X-%X]",
				range_lo,
				range_hi);
		अन्यथा अणु
			प्र_लिखो(alias + म_माप(alias),
				range_lo < 0x9 ? "[%X-9" : "[%X",
				range_lo);
			प्र_लिखो(alias + म_माप(alias),
				range_hi > 0xA ? "A-%X]" : "%X]",
				range_hi);
		पूर्ण
	पूर्ण
	अगर (bcdDevice_initial_digits < (माप(bcdDevice_lo) * 2 - 1))
		म_जोड़ो(alias, "*");

	ADD(alias, "dc", match_flags&USB_DEVICE_ID_MATCH_DEV_CLASS,
	    bDeviceClass);
	ADD(alias, "dsc", match_flags&USB_DEVICE_ID_MATCH_DEV_SUBCLASS,
	    bDeviceSubClass);
	ADD(alias, "dp", match_flags&USB_DEVICE_ID_MATCH_DEV_PROTOCOL,
	    bDeviceProtocol);
	ADD(alias, "ic", match_flags&USB_DEVICE_ID_MATCH_INT_CLASS,
	    bInterfaceClass);
	ADD(alias, "isc", match_flags&USB_DEVICE_ID_MATCH_INT_SUBCLASS,
	    bInterfaceSubClass);
	ADD(alias, "ip", match_flags&USB_DEVICE_ID_MATCH_INT_PROTOCOL,
	    bInterfaceProtocol);
	ADD(alias, "in", match_flags&USB_DEVICE_ID_MATCH_INT_NUMBER,
	    bInterfaceNumber);

	add_wildcard(alias);
	buf_म_लिखो(&mod->dev_table_buf,
		   "MODULE_ALIAS(\"%s\");\n", alias);
पूर्ण

/* Handles increment/decrement of BCD क्रमmatted पूर्णांकegers */
/* Returns the previous value, so it works like i++ or i-- */
अटल अचिन्हित पूर्णांक incbcd(अचिन्हित पूर्णांक *bcd,
			   पूर्णांक inc,
			   अचिन्हित अक्षर max,
			   माप_प्रकार अक्षरs)
अणु
	अचिन्हित पूर्णांक init = *bcd, i, j;
	अचिन्हित दीर्घ दीर्घ c, dec = 0;

	/* If bcd is not in BCD क्रमmat, just increment */
	अगर (max > 0x9) अणु
		*bcd += inc;
		वापस init;
	पूर्ण

	/* Convert BCD to Decimal */
	क्रम (i=0 ; i < अक्षरs ; i++) अणु
		c = (*bcd >> (i << 2)) & 0xf;
		c = c > 9 ? 9 : c; /* क्रमce to bcd just in हाल */
		क्रम (j=0 ; j < i ; j++)
			c = c * 10;
		dec += c;
	पूर्ण

	/* Do our increment/decrement */
	dec += inc;
	*bcd  = 0;

	/* Convert back to BCD */
	क्रम (i=0 ; i < अक्षरs ; i++) अणु
		क्रम (c=1,j=0 ; j < i ; j++)
			c = c * 10;
		c = (dec / c) % 10;
		*bcd += c << (i << 2);
	पूर्ण
	वापस init;
पूर्ण

अटल व्योम करो_usb_entry_multi(व्योम *symval, काष्ठा module *mod)
अणु
	अचिन्हित पूर्णांक devlo, devhi;
	अचिन्हित अक्षर chi, clo, max;
	पूर्णांक ndigits;

	DEF_FIELD(symval, usb_device_id, match_flags);
	DEF_FIELD(symval, usb_device_id, idVenकरोr);
	DEF_FIELD(symval, usb_device_id, idProduct);
	DEF_FIELD(symval, usb_device_id, bcdDevice_lo);
	DEF_FIELD(symval, usb_device_id, bcdDevice_hi);
	DEF_FIELD(symval, usb_device_id, bDeviceClass);
	DEF_FIELD(symval, usb_device_id, bInterfaceClass);

	devlo = match_flags & USB_DEVICE_ID_MATCH_DEV_LO ?
		bcdDevice_lo : 0x0U;
	devhi = match_flags & USB_DEVICE_ID_MATCH_DEV_HI ?
		bcdDevice_hi : ~0x0U;

	/* Figure out अगर this entry is in bcd or hex क्रमmat */
	max = 0x9; /* Default to decimal क्रमmat */
	क्रम (ndigits = 0 ; ndigits < माप(bcdDevice_lo) * 2 ; ndigits++) अणु
		clo = (devlo >> (ndigits << 2)) & 0xf;
		chi = ((devhi > 0x9999 ? 0x9999 : devhi) >> (ndigits << 2)) & 0xf;
		अगर (clo > max || chi > max) अणु
			max = 0xf;
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * Some modules (visor) have empty slots as placeholder क्रम
	 * run-समय specअगरication that results in catch-all alias
	 */
	अगर (!(idVenकरोr | idProduct | bDeviceClass | bInterfaceClass))
		वापस;

	/* Convert numeric bcdDevice range पूर्णांकo fnmatch-able pattern(s) */
	क्रम (ndigits = माप(bcdDevice_lo) * 2 - 1; devlo <= devhi; ndigits--) अणु
		clo = devlo & 0xf;
		chi = devhi & 0xf;
		अगर (chi > max)	/* If we are in bcd mode, truncate अगर necessary */
			chi = max;
		devlo >>= 4;
		devhi >>= 4;

		अगर (devlo == devhi || !ndigits) अणु
			करो_usb_entry(symval, devlo, ndigits, clo, chi, max, mod);
			अवरोध;
		पूर्ण

		अगर (clo > 0x0)
			करो_usb_entry(symval,
				     incbcd(&devlo, 1, max,
					    माप(bcdDevice_lo) * 2),
				     ndigits, clo, max, max, mod);

		अगर (chi < max)
			करो_usb_entry(symval,
				     incbcd(&devhi, -1, max,
					    माप(bcdDevice_lo) * 2),
				     ndigits, 0x0, chi, max, mod);
	पूर्ण
पूर्ण

अटल व्योम करो_usb_table(व्योम *symval, अचिन्हित दीर्घ size,
			 काष्ठा module *mod)
अणु
	अचिन्हित पूर्णांक i;
	स्थिर अचिन्हित दीर्घ id_size = SIZE_usb_device_id;

	device_id_check(mod->name, "usb", size, id_size, symval);

	/* Leave last one: it's the terminator. */
	size -= id_size;

	क्रम (i = 0; i < size; i += id_size)
		करो_usb_entry_multi(symval + i, mod);
पूर्ण

अटल व्योम करो_of_entry_multi(व्योम *symval, काष्ठा module *mod)
अणु
	अक्षर alias[500];
	पूर्णांक len;
	अक्षर *पंचांगp;

	DEF_FIELD_ADDR(symval, of_device_id, name);
	DEF_FIELD_ADDR(symval, of_device_id, type);
	DEF_FIELD_ADDR(symval, of_device_id, compatible);

	len = प्र_लिखो(alias, "of:N%sT%s", (*name)[0] ? *name : "*",
		      (*type)[0] ? *type : "*");

	अगर ((*compatible)[0])
		प्र_लिखो(&alias[len], "%sC%s", (*type)[0] ? "*" : "",
			*compatible);

	/* Replace all whitespace with underscores */
	क्रम (पंचांगp = alias; पंचांगp && *पंचांगp; पंचांगp++)
		अगर (है_खाली(*पंचांगp))
			*पंचांगp = '_';

	buf_म_लिखो(&mod->dev_table_buf, "MODULE_ALIAS(\"%s\");\n", alias);
	म_जोड़ो(alias, "C");
	add_wildcard(alias);
	buf_म_लिखो(&mod->dev_table_buf, "MODULE_ALIAS(\"%s\");\n", alias);
पूर्ण

अटल व्योम करो_of_table(व्योम *symval, अचिन्हित दीर्घ size,
			काष्ठा module *mod)
अणु
	अचिन्हित पूर्णांक i;
	स्थिर अचिन्हित दीर्घ id_size = SIZE_of_device_id;

	device_id_check(mod->name, "of", size, id_size, symval);

	/* Leave last one: it's the terminator. */
	size -= id_size;

	क्रम (i = 0; i < size; i += id_size)
		करो_of_entry_multi(symval + i, mod);
पूर्ण

/* Looks like: hid:bNvNpN */
अटल पूर्णांक करो_hid_entry(स्थिर अक्षर *filename,
			     व्योम *symval, अक्षर *alias)
अणु
	DEF_FIELD(symval, hid_device_id, bus);
	DEF_FIELD(symval, hid_device_id, group);
	DEF_FIELD(symval, hid_device_id, venकरोr);
	DEF_FIELD(symval, hid_device_id, product);

	प्र_लिखो(alias, "hid:");
	ADD(alias, "b", bus != HID_BUS_ANY, bus);
	ADD(alias, "g", group != HID_GROUP_ANY, group);
	ADD(alias, "v", venकरोr != HID_ANY_ID, venकरोr);
	ADD(alias, "p", product != HID_ANY_ID, product);

	वापस 1;
पूर्ण

/* Looks like: ieee1394:venNmoNspNverN */
अटल पूर्णांक करो_ieee1394_entry(स्थिर अक्षर *filename,
			     व्योम *symval, अक्षर *alias)
अणु
	DEF_FIELD(symval, ieee1394_device_id, match_flags);
	DEF_FIELD(symval, ieee1394_device_id, venकरोr_id);
	DEF_FIELD(symval, ieee1394_device_id, model_id);
	DEF_FIELD(symval, ieee1394_device_id, specअगरier_id);
	DEF_FIELD(symval, ieee1394_device_id, version);

	म_नकल(alias, "ieee1394:");
	ADD(alias, "ven", match_flags & IEEE1394_MATCH_VENDOR_ID,
	    venकरोr_id);
	ADD(alias, "mo", match_flags & IEEE1394_MATCH_MODEL_ID,
	    model_id);
	ADD(alias, "sp", match_flags & IEEE1394_MATCH_SPECIFIER_ID,
	    specअगरier_id);
	ADD(alias, "ver", match_flags & IEEE1394_MATCH_VERSION,
	    version);

	add_wildcard(alias);
	वापस 1;
पूर्ण

/* Looks like: pci:vNdNsvNsdNbcNscNiN. */
अटल पूर्णांक करो_pci_entry(स्थिर अक्षर *filename,
			व्योम *symval, अक्षर *alias)
अणु
	/* Class field can be भागided पूर्णांकo these three. */
	अचिन्हित अक्षर baseclass, subclass, पूर्णांकerface,
		baseclass_mask, subclass_mask, पूर्णांकerface_mask;

	DEF_FIELD(symval, pci_device_id, venकरोr);
	DEF_FIELD(symval, pci_device_id, device);
	DEF_FIELD(symval, pci_device_id, subvenकरोr);
	DEF_FIELD(symval, pci_device_id, subdevice);
	DEF_FIELD(symval, pci_device_id, class);
	DEF_FIELD(symval, pci_device_id, class_mask);

	म_नकल(alias, "pci:");
	ADD(alias, "v", venकरोr != PCI_ANY_ID, venकरोr);
	ADD(alias, "d", device != PCI_ANY_ID, device);
	ADD(alias, "sv", subvenकरोr != PCI_ANY_ID, subvenकरोr);
	ADD(alias, "sd", subdevice != PCI_ANY_ID, subdevice);

	baseclass = (class) >> 16;
	baseclass_mask = (class_mask) >> 16;
	subclass = (class) >> 8;
	subclass_mask = (class_mask) >> 8;
	पूर्णांकerface = class;
	पूर्णांकerface_mask = class_mask;

	अगर ((baseclass_mask != 0 && baseclass_mask != 0xFF)
	    || (subclass_mask != 0 && subclass_mask != 0xFF)
	    || (पूर्णांकerface_mask != 0 && पूर्णांकerface_mask != 0xFF)) अणु
		warn("Can't handle masks in %s:%04X\n",
		     filename, class_mask);
		वापस 0;
	पूर्ण

	ADD(alias, "bc", baseclass_mask == 0xFF, baseclass);
	ADD(alias, "sc", subclass_mask == 0xFF, subclass);
	ADD(alias, "i", पूर्णांकerface_mask == 0xFF, पूर्णांकerface);
	add_wildcard(alias);
	वापस 1;
पूर्ण

/* looks like: "ccw:tNmNdtNdmN" */
अटल पूर्णांक करो_ccw_entry(स्थिर अक्षर *filename,
			व्योम *symval, अक्षर *alias)
अणु
	DEF_FIELD(symval, ccw_device_id, match_flags);
	DEF_FIELD(symval, ccw_device_id, cu_type);
	DEF_FIELD(symval, ccw_device_id, cu_model);
	DEF_FIELD(symval, ccw_device_id, dev_type);
	DEF_FIELD(symval, ccw_device_id, dev_model);

	म_नकल(alias, "ccw:");
	ADD(alias, "t", match_flags&CCW_DEVICE_ID_MATCH_CU_TYPE,
	    cu_type);
	ADD(alias, "m", match_flags&CCW_DEVICE_ID_MATCH_CU_MODEL,
	    cu_model);
	ADD(alias, "dt", match_flags&CCW_DEVICE_ID_MATCH_DEVICE_TYPE,
	    dev_type);
	ADD(alias, "dm", match_flags&CCW_DEVICE_ID_MATCH_DEVICE_MODEL,
	    dev_model);
	add_wildcard(alias);
	वापस 1;
पूर्ण

/* looks like: "ap:tN" */
अटल पूर्णांक करो_ap_entry(स्थिर अक्षर *filename,
		       व्योम *symval, अक्षर *alias)
अणु
	DEF_FIELD(symval, ap_device_id, dev_type);

	प्र_लिखो(alias, "ap:t%02X*", dev_type);
	वापस 1;
पूर्ण

/* looks like: "css:tN" */
अटल पूर्णांक करो_css_entry(स्थिर अक्षर *filename,
			व्योम *symval, अक्षर *alias)
अणु
	DEF_FIELD(symval, css_device_id, type);

	प्र_लिखो(alias, "css:t%01X", type);
	वापस 1;
पूर्ण

/* Looks like: "serio:tyNprNidNexN" */
अटल पूर्णांक करो_serio_entry(स्थिर अक्षर *filename,
			  व्योम *symval, अक्षर *alias)
अणु
	DEF_FIELD(symval, serio_device_id, type);
	DEF_FIELD(symval, serio_device_id, proto);
	DEF_FIELD(symval, serio_device_id, id);
	DEF_FIELD(symval, serio_device_id, extra);

	म_नकल(alias, "serio:");
	ADD(alias, "ty", type != SERIO_ANY, type);
	ADD(alias, "pr", proto != SERIO_ANY, proto);
	ADD(alias, "id", id != SERIO_ANY, id);
	ADD(alias, "ex", extra != SERIO_ANY, extra);

	add_wildcard(alias);
	वापस 1;
पूर्ण

/* looks like: "acpi:ACPI0003" or "acpi:PNP0C0B" or "acpi:LNXVIDEO" or
 *             "acpi:bbsspp" (bb=base-class, ss=sub-class, pp=prog-अगर)
 *
 * NOTE: Each driver should use one of the following : _HID, _CIDs
 *       or _CLS. Also, bb, ss, and pp can be substituted with ??
 *       as करोn't care byte.
 */
अटल पूर्णांक करो_acpi_entry(स्थिर अक्षर *filename,
			व्योम *symval, अक्षर *alias)
अणु
	DEF_FIELD_ADDR(symval, acpi_device_id, id);
	DEF_FIELD_ADDR(symval, acpi_device_id, cls);
	DEF_FIELD_ADDR(symval, acpi_device_id, cls_msk);

	अगर (id && म_माप((स्थिर अक्षर *)*id))
		प्र_लिखो(alias, "acpi*:%s:*", *id);
	अन्यथा अगर (cls) अणु
		पूर्णांक i, byte_shअगरt, cnt = 0;
		अचिन्हित पूर्णांक msk;

		प्र_लिखो(&alias[cnt], "acpi*:");
		cnt = 6;
		क्रम (i = 1; i <= 3; i++) अणु
			byte_shअगरt = 8 * (3-i);
			msk = (*cls_msk >> byte_shअगरt) & 0xFF;
			अगर (msk)
				प्र_लिखो(&alias[cnt], "%02x",
					(*cls >> byte_shअगरt) & 0xFF);
			अन्यथा
				प्र_लिखो(&alias[cnt], "??");
			cnt += 2;
		पूर्ण
		प्र_लिखो(&alias[cnt], ":*");
	पूर्ण
	वापस 1;
पूर्ण

/* looks like: "pnp:dD" */
अटल व्योम करो_pnp_device_entry(व्योम *symval, अचिन्हित दीर्घ size,
				काष्ठा module *mod)
अणु
	स्थिर अचिन्हित दीर्घ id_size = SIZE_pnp_device_id;
	स्थिर अचिन्हित पूर्णांक count = (size / id_size)-1;
	अचिन्हित पूर्णांक i;

	device_id_check(mod->name, "pnp", size, id_size, symval);

	क्रम (i = 0; i < count; i++) अणु
		DEF_FIELD_ADDR(symval + i*id_size, pnp_device_id, id);
		अक्षर acpi_id[माप(*id)];
		पूर्णांक j;

		buf_म_लिखो(&mod->dev_table_buf,
			   "MODULE_ALIAS(\"pnp:d%s*\");\n", *id);

		/* fix broken pnp bus lowercasing */
		क्रम (j = 0; j < माप(acpi_id); j++)
			acpi_id[j] = बड़े((*id)[j]);
		buf_म_लिखो(&mod->dev_table_buf,
			   "MODULE_ALIAS(\"acpi*:%s:*\");\n", acpi_id);
	पूर्ण
पूर्ण

/* looks like: "pnp:dD" क्रम every device of the card */
अटल व्योम करो_pnp_card_entries(व्योम *symval, अचिन्हित दीर्घ size,
				काष्ठा module *mod)
अणु
	स्थिर अचिन्हित दीर्घ id_size = SIZE_pnp_card_device_id;
	स्थिर अचिन्हित पूर्णांक count = (size / id_size)-1;
	अचिन्हित पूर्णांक i;

	device_id_check(mod->name, "pnp", size, id_size, symval);

	क्रम (i = 0; i < count; i++) अणु
		अचिन्हित पूर्णांक j;
		DEF_FIELD_ADDR(symval + i * id_size, pnp_card_device_id, devs);

		क्रम (j = 0; j < PNP_MAX_DEVICES; j++) अणु
			स्थिर अक्षर *id = (अक्षर *)(*devs)[j].id;
			पूर्णांक i2, j2;
			पूर्णांक dup = 0;

			अगर (!id[0])
				अवरोध;

			/* find duplicate, alपढ़ोy added value */
			क्रम (i2 = 0; i2 < i && !dup; i2++) अणु
				DEF_FIELD_ADDR_VAR(symval + i2 * id_size,
						   pnp_card_device_id,
						   devs, devs_dup);

				क्रम (j2 = 0; j2 < PNP_MAX_DEVICES; j2++) अणु
					स्थिर अक्षर *id2 =
						(अक्षर *)(*devs_dup)[j2].id;

					अगर (!id2[0])
						अवरोध;

					अगर (!म_भेद(id, id2)) अणु
						dup = 1;
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण

			/* add an inभागidual alias क्रम every device entry */
			अगर (!dup) अणु
				अक्षर acpi_id[PNP_ID_LEN];
				पूर्णांक k;

				buf_म_लिखो(&mod->dev_table_buf,
					   "MODULE_ALIAS(\"pnp:d%s*\");\n", id);

				/* fix broken pnp bus lowercasing */
				क्रम (k = 0; k < माप(acpi_id); k++)
					acpi_id[k] = बड़े(id[k]);
				buf_म_लिखो(&mod->dev_table_buf,
					   "MODULE_ALIAS(\"acpi*:%s:*\");\n", acpi_id);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/* Looks like: pcmcia:mNcNfNfnNpfnNvaNvbNvcNvdN. */
अटल पूर्णांक करो_pcmcia_entry(स्थिर अक्षर *filename,
			   व्योम *symval, अक्षर *alias)
अणु
	अचिन्हित पूर्णांक i;
	DEF_FIELD(symval, pcmcia_device_id, match_flags);
	DEF_FIELD(symval, pcmcia_device_id, manf_id);
	DEF_FIELD(symval, pcmcia_device_id, card_id);
	DEF_FIELD(symval, pcmcia_device_id, func_id);
	DEF_FIELD(symval, pcmcia_device_id, function);
	DEF_FIELD(symval, pcmcia_device_id, device_no);
	DEF_FIELD_ADDR(symval, pcmcia_device_id, prod_id_hash);

	क्रम (i=0; i<4; i++) अणु
		(*prod_id_hash)[i] = TO_NATIVE((*prod_id_hash)[i]);
	पूर्ण

	म_नकल(alias, "pcmcia:");
	ADD(alias, "m", match_flags & PCMCIA_DEV_ID_MATCH_MANF_ID,
	    manf_id);
	ADD(alias, "c", match_flags & PCMCIA_DEV_ID_MATCH_CARD_ID,
	    card_id);
	ADD(alias, "f", match_flags & PCMCIA_DEV_ID_MATCH_FUNC_ID,
	    func_id);
	ADD(alias, "fn", match_flags & PCMCIA_DEV_ID_MATCH_FUNCTION,
	    function);
	ADD(alias, "pfn", match_flags & PCMCIA_DEV_ID_MATCH_DEVICE_NO,
	    device_no);
	ADD(alias, "pa", match_flags & PCMCIA_DEV_ID_MATCH_PROD_ID1, (*prod_id_hash)[0]);
	ADD(alias, "pb", match_flags & PCMCIA_DEV_ID_MATCH_PROD_ID2, (*prod_id_hash)[1]);
	ADD(alias, "pc", match_flags & PCMCIA_DEV_ID_MATCH_PROD_ID3, (*prod_id_hash)[2]);
	ADD(alias, "pd", match_flags & PCMCIA_DEV_ID_MATCH_PROD_ID4, (*prod_id_hash)[3]);

	add_wildcard(alias);
	वापस 1;
पूर्ण

अटल पूर्णांक करो_vio_entry(स्थिर अक्षर *filename, व्योम *symval,
		अक्षर *alias)
अणु
	अक्षर *पंचांगp;
	DEF_FIELD_ADDR(symval, vio_device_id, type);
	DEF_FIELD_ADDR(symval, vio_device_id, compat);

	प्र_लिखो(alias, "vio:T%sS%s", (*type)[0] ? *type : "*",
			(*compat)[0] ? *compat : "*");

	/* Replace all whitespace with underscores */
	क्रम (पंचांगp = alias; पंचांगp && *पंचांगp; पंचांगp++)
		अगर (है_खाली (*पंचांगp))
			*पंचांगp = '_';

	add_wildcard(alias);
	वापस 1;
पूर्ण

#घोषणा ARRAY_SIZE(x) (माप(x) / माप((x)[0]))

अटल व्योम करो_input(अक्षर *alias,
		     kernel_uदीर्घ_t *arr, अचिन्हित पूर्णांक min, अचिन्हित पूर्णांक max)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = min / BITS_PER_LONG; i < max / BITS_PER_LONG + 1; i++)
		arr[i] = TO_NATIVE(arr[i]);
	क्रम (i = min; i < max; i++)
		अगर (arr[i / BITS_PER_LONG] & (1L << (i%BITS_PER_LONG)))
			प्र_लिखो(alias + म_माप(alias), "%X,*", i);
पूर्ण

/* input:b0v0p0e0-eXkXrXaXmXlXsXfXwX where X is comma-separated %02X. */
अटल पूर्णांक करो_input_entry(स्थिर अक्षर *filename, व्योम *symval,
			  अक्षर *alias)
अणु
	DEF_FIELD(symval, input_device_id, flags);
	DEF_FIELD(symval, input_device_id, bustype);
	DEF_FIELD(symval, input_device_id, venकरोr);
	DEF_FIELD(symval, input_device_id, product);
	DEF_FIELD(symval, input_device_id, version);
	DEF_FIELD_ADDR(symval, input_device_id, evbit);
	DEF_FIELD_ADDR(symval, input_device_id, keybit);
	DEF_FIELD_ADDR(symval, input_device_id, relbit);
	DEF_FIELD_ADDR(symval, input_device_id, असलbit);
	DEF_FIELD_ADDR(symval, input_device_id, mscbit);
	DEF_FIELD_ADDR(symval, input_device_id, ledbit);
	DEF_FIELD_ADDR(symval, input_device_id, sndbit);
	DEF_FIELD_ADDR(symval, input_device_id, ffbit);
	DEF_FIELD_ADDR(symval, input_device_id, swbit);

	प्र_लिखो(alias, "input:");

	ADD(alias, "b", flags & INPUT_DEVICE_ID_MATCH_BUS, bustype);
	ADD(alias, "v", flags & INPUT_DEVICE_ID_MATCH_VENDOR, venकरोr);
	ADD(alias, "p", flags & INPUT_DEVICE_ID_MATCH_PRODUCT, product);
	ADD(alias, "e", flags & INPUT_DEVICE_ID_MATCH_VERSION, version);

	प्र_लिखो(alias + म_माप(alias), "-e*");
	अगर (flags & INPUT_DEVICE_ID_MATCH_EVBIT)
		करो_input(alias, *evbit, 0, INPUT_DEVICE_ID_EV_MAX);
	प्र_लिखो(alias + म_माप(alias), "k*");
	अगर (flags & INPUT_DEVICE_ID_MATCH_KEYBIT)
		करो_input(alias, *keybit,
			 INPUT_DEVICE_ID_KEY_MIN_INTERESTING,
			 INPUT_DEVICE_ID_KEY_MAX);
	प्र_लिखो(alias + म_माप(alias), "r*");
	अगर (flags & INPUT_DEVICE_ID_MATCH_RELBIT)
		करो_input(alias, *relbit, 0, INPUT_DEVICE_ID_REL_MAX);
	प्र_लिखो(alias + म_माप(alias), "a*");
	अगर (flags & INPUT_DEVICE_ID_MATCH_ABSBIT)
		करो_input(alias, *असलbit, 0, INPUT_DEVICE_ID_ABS_MAX);
	प्र_लिखो(alias + म_माप(alias), "m*");
	अगर (flags & INPUT_DEVICE_ID_MATCH_MSCIT)
		करो_input(alias, *mscbit, 0, INPUT_DEVICE_ID_MSC_MAX);
	प्र_लिखो(alias + म_माप(alias), "l*");
	अगर (flags & INPUT_DEVICE_ID_MATCH_LEDBIT)
		करो_input(alias, *ledbit, 0, INPUT_DEVICE_ID_LED_MAX);
	प्र_लिखो(alias + म_माप(alias), "s*");
	अगर (flags & INPUT_DEVICE_ID_MATCH_SNDBIT)
		करो_input(alias, *sndbit, 0, INPUT_DEVICE_ID_SND_MAX);
	प्र_लिखो(alias + म_माप(alias), "f*");
	अगर (flags & INPUT_DEVICE_ID_MATCH_FFBIT)
		करो_input(alias, *ffbit, 0, INPUT_DEVICE_ID_FF_MAX);
	प्र_लिखो(alias + म_माप(alias), "w*");
	अगर (flags & INPUT_DEVICE_ID_MATCH_SWBIT)
		करो_input(alias, *swbit, 0, INPUT_DEVICE_ID_SW_MAX);
	वापस 1;
पूर्ण

अटल पूर्णांक करो_eisa_entry(स्थिर अक्षर *filename, व्योम *symval,
		अक्षर *alias)
अणु
	DEF_FIELD_ADDR(symval, eisa_device_id, sig);
	अगर (sig[0])
		प्र_लिखो(alias, EISA_DEVICE_MODALIAS_FMT "*", *sig);
	अन्यथा
		म_जोड़ो(alias, "*");
	वापस 1;
पूर्ण

/* Looks like: parisc:tNhvNrevNsvN */
अटल पूर्णांक करो_parisc_entry(स्थिर अक्षर *filename, व्योम *symval,
		अक्षर *alias)
अणु
	DEF_FIELD(symval, parisc_device_id, hw_type);
	DEF_FIELD(symval, parisc_device_id, hversion);
	DEF_FIELD(symval, parisc_device_id, hversion_rev);
	DEF_FIELD(symval, parisc_device_id, sversion);

	म_नकल(alias, "parisc:");
	ADD(alias, "t", hw_type != PA_HWTYPE_ANY_ID, hw_type);
	ADD(alias, "hv", hversion != PA_HVERSION_ANY_ID, hversion);
	ADD(alias, "rev", hversion_rev != PA_HVERSION_REV_ANY_ID, hversion_rev);
	ADD(alias, "sv", sversion != PA_SVERSION_ANY_ID, sversion);

	add_wildcard(alias);
	वापस 1;
पूर्ण

/* Looks like: sdio:cNvNdN. */
अटल पूर्णांक करो_sdio_entry(स्थिर अक्षर *filename,
			व्योम *symval, अक्षर *alias)
अणु
	DEF_FIELD(symval, sdio_device_id, class);
	DEF_FIELD(symval, sdio_device_id, venकरोr);
	DEF_FIELD(symval, sdio_device_id, device);

	म_नकल(alias, "sdio:");
	ADD(alias, "c", class != (__u8)SDIO_ANY_ID, class);
	ADD(alias, "v", venकरोr != (__u16)SDIO_ANY_ID, venकरोr);
	ADD(alias, "d", device != (__u16)SDIO_ANY_ID, device);
	add_wildcard(alias);
	वापस 1;
पूर्ण

/* Looks like: ssb:vNidNrevN. */
अटल पूर्णांक करो_ssb_entry(स्थिर अक्षर *filename,
			व्योम *symval, अक्षर *alias)
अणु
	DEF_FIELD(symval, ssb_device_id, venकरोr);
	DEF_FIELD(symval, ssb_device_id, coreid);
	DEF_FIELD(symval, ssb_device_id, revision);

	म_नकल(alias, "ssb:");
	ADD(alias, "v", venकरोr != SSB_ANY_VENDOR, venकरोr);
	ADD(alias, "id", coreid != SSB_ANY_ID, coreid);
	ADD(alias, "rev", revision != SSB_ANY_REV, revision);
	add_wildcard(alias);
	वापस 1;
पूर्ण

/* Looks like: bcma:mNidNrevNclN. */
अटल पूर्णांक करो_bcma_entry(स्थिर अक्षर *filename,
			 व्योम *symval, अक्षर *alias)
अणु
	DEF_FIELD(symval, bcma_device_id, manuf);
	DEF_FIELD(symval, bcma_device_id, id);
	DEF_FIELD(symval, bcma_device_id, rev);
	DEF_FIELD(symval, bcma_device_id, class);

	म_नकल(alias, "bcma:");
	ADD(alias, "m", manuf != BCMA_ANY_MANUF, manuf);
	ADD(alias, "id", id != BCMA_ANY_ID, id);
	ADD(alias, "rev", rev != BCMA_ANY_REV, rev);
	ADD(alias, "cl", class != BCMA_ANY_CLASS, class);
	add_wildcard(alias);
	वापस 1;
पूर्ण

/* Looks like: virtio:dNvN */
अटल पूर्णांक करो_virtio_entry(स्थिर अक्षर *filename, व्योम *symval,
			   अक्षर *alias)
अणु
	DEF_FIELD(symval, virtio_device_id, device);
	DEF_FIELD(symval, virtio_device_id, venकरोr);

	म_नकल(alias, "virtio:");
	ADD(alias, "d", device != VIRTIO_DEV_ANY_ID, device);
	ADD(alias, "v", venकरोr != VIRTIO_DEV_ANY_ID, venकरोr);

	add_wildcard(alias);
	वापस 1;
पूर्ण

/*
 * Looks like: vmbus:guid
 * Each byte of the guid will be represented by two hex अक्षरacters
 * in the name.
 */

अटल पूर्णांक करो_vmbus_entry(स्थिर अक्षर *filename, व्योम *symval,
			  अक्षर *alias)
अणु
	पूर्णांक i;
	DEF_FIELD_ADDR(symval, hv_vmbus_device_id, guid);
	अक्षर guid_name[(माप(*guid) + 1) * 2];

	क्रम (i = 0; i < (माप(*guid) * 2); i += 2)
		प्र_लिखो(&guid_name[i], "%02x", TO_NATIVE((guid->b)[i/2]));

	म_नकल(alias, "vmbus:");
	म_जोड़ो(alias, guid_name);

	वापस 1;
पूर्ण

/* Looks like: rpmsg:S */
अटल पूर्णांक करो_rpmsg_entry(स्थिर अक्षर *filename, व्योम *symval,
			  अक्षर *alias)
अणु
	DEF_FIELD_ADDR(symval, rpmsg_device_id, name);
	प्र_लिखो(alias, RPMSG_DEVICE_MODALIAS_FMT, *name);

	वापस 1;
पूर्ण

/* Looks like: i2c:S */
अटल पूर्णांक करो_i2c_entry(स्थिर अक्षर *filename, व्योम *symval,
			अक्षर *alias)
अणु
	DEF_FIELD_ADDR(symval, i2c_device_id, name);
	प्र_लिखो(alias, I2C_MODULE_PREFIX "%s", *name);

	वापस 1;
पूर्ण

अटल पूर्णांक करो_i3c_entry(स्थिर अक्षर *filename, व्योम *symval,
			अक्षर *alias)
अणु
	DEF_FIELD(symval, i3c_device_id, match_flags);
	DEF_FIELD(symval, i3c_device_id, dcr);
	DEF_FIELD(symval, i3c_device_id, manuf_id);
	DEF_FIELD(symval, i3c_device_id, part_id);
	DEF_FIELD(symval, i3c_device_id, extra_info);

	म_नकल(alias, "i3c:");
	ADD(alias, "dcr", match_flags & I3C_MATCH_DCR, dcr);
	ADD(alias, "manuf", match_flags & I3C_MATCH_MANUF, manuf_id);
	ADD(alias, "part", match_flags & I3C_MATCH_PART, part_id);
	ADD(alias, "ext", match_flags & I3C_MATCH_EXTRA_INFO, extra_info);

	वापस 1;
पूर्ण

/* Looks like: spi:S */
अटल पूर्णांक करो_spi_entry(स्थिर अक्षर *filename, व्योम *symval,
			अक्षर *alias)
अणु
	DEF_FIELD_ADDR(symval, spi_device_id, name);
	प्र_लिखो(alias, SPI_MODULE_PREFIX "%s", *name);

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा dmअगरield अणु
	स्थिर अक्षर *prefix;
	पूर्णांक field;
पूर्ण dmi_fields[] = अणु
	अणु "bvn", DMI_BIOS_VENDOR पूर्ण,
	अणु "bvr", DMI_BIOS_VERSION पूर्ण,
	अणु "bd",  DMI_BIOS_DATE पूर्ण,
	अणु "br",  DMI_BIOS_RELEASE पूर्ण,
	अणु "efr", DMI_EC_FIRMWARE_RELEASE पूर्ण,
	अणु "svn", DMI_SYS_VENDOR पूर्ण,
	अणु "pn",  DMI_PRODUCT_NAME पूर्ण,
	अणु "pvr", DMI_PRODUCT_VERSION पूर्ण,
	अणु "rvn", DMI_BOARD_VENDOR पूर्ण,
	अणु "rn",  DMI_BOARD_NAME पूर्ण,
	अणु "rvr", DMI_BOARD_VERSION पूर्ण,
	अणु "cvn", DMI_CHASSIS_VENDOR पूर्ण,
	अणु "ct",  DMI_CHASSIS_TYPE पूर्ण,
	अणु "cvr", DMI_CHASSIS_VERSION पूर्ण,
	अणु शून्य,  DMI_NONE पूर्ण
पूर्ण;

अटल व्योम dmi_ascii_filter(अक्षर *d, स्थिर अक्षर *s)
अणु
	/* Filter out अक्षरacters we करोn't want to see in the modalias string */
	क्रम (; *s; s++)
		अगर (*s > ' ' && *s < 127 && *s != ':')
			*(d++) = *s;

	*d = 0;
पूर्ण


अटल पूर्णांक करो_dmi_entry(स्थिर अक्षर *filename, व्योम *symval,
			अक्षर *alias)
अणु
	पूर्णांक i, j;
	DEF_FIELD_ADDR(symval, dmi_प्रणाली_id, matches);
	प्र_लिखो(alias, "dmi*");

	क्रम (i = 0; i < ARRAY_SIZE(dmi_fields); i++) अणु
		क्रम (j = 0; j < 4; j++) अणु
			अगर ((*matches)[j].slot &&
			    (*matches)[j].slot == dmi_fields[i].field) अणु
				प्र_लिखो(alias + म_माप(alias), ":%s*",
					dmi_fields[i].prefix);
				dmi_ascii_filter(alias + म_माप(alias),
						 (*matches)[j].substr);
				म_जोड़ो(alias, "*");
			पूर्ण
		पूर्ण
	पूर्ण

	म_जोड़ो(alias, ":");
	वापस 1;
पूर्ण

अटल पूर्णांक करो_platक्रमm_entry(स्थिर अक्षर *filename,
			     व्योम *symval, अक्षर *alias)
अणु
	DEF_FIELD_ADDR(symval, platक्रमm_device_id, name);
	प्र_लिखो(alias, PLATFORM_MODULE_PREFIX "%s", *name);
	वापस 1;
पूर्ण

अटल पूर्णांक करो_mdio_entry(स्थिर अक्षर *filename,
			 व्योम *symval, अक्षर *alias)
अणु
	पूर्णांक i;
	DEF_FIELD(symval, mdio_device_id, phy_id);
	DEF_FIELD(symval, mdio_device_id, phy_id_mask);

	alias += प्र_लिखो(alias, MDIO_MODULE_PREFIX);

	क्रम (i = 0; i < 32; i++) अणु
		अगर (!((phy_id_mask >> (31-i)) & 1))
			*(alias++) = '?';
		अन्यथा अगर ((phy_id >> (31-i)) & 1)
			*(alias++) = '1';
		अन्यथा
			*(alias++) = '0';
	पूर्ण

	/* Terminate the string */
	*alias = 0;

	वापस 1;
पूर्ण

/* Looks like: zorro:iN. */
अटल पूर्णांक करो_zorro_entry(स्थिर अक्षर *filename, व्योम *symval,
			  अक्षर *alias)
अणु
	DEF_FIELD(symval, zorro_device_id, id);
	म_नकल(alias, "zorro:");
	ADD(alias, "i", id != ZORRO_WILDCARD, id);
	वापस 1;
पूर्ण

/* looks like: "pnp:dD" */
अटल पूर्णांक करो_isapnp_entry(स्थिर अक्षर *filename,
			   व्योम *symval, अक्षर *alias)
अणु
	DEF_FIELD(symval, isapnp_device_id, venकरोr);
	DEF_FIELD(symval, isapnp_device_id, function);
	प्र_लिखो(alias, "pnp:d%c%c%c%x%x%x%x*",
		'A' + ((venकरोr >> 2) & 0x3f) - 1,
		'A' + (((venकरोr & 3) << 3) | ((venकरोr >> 13) & 7)) - 1,
		'A' + ((venकरोr >> 8) & 0x1f) - 1,
		(function >> 4) & 0x0f, function & 0x0f,
		(function >> 12) & 0x0f, (function >> 8) & 0x0f);
	वापस 1;
पूर्ण

/* Looks like: "ipack:fNvNdN". */
अटल पूर्णांक करो_ipack_entry(स्थिर अक्षर *filename,
			  व्योम *symval, अक्षर *alias)
अणु
	DEF_FIELD(symval, ipack_device_id, क्रमmat);
	DEF_FIELD(symval, ipack_device_id, venकरोr);
	DEF_FIELD(symval, ipack_device_id, device);
	म_नकल(alias, "ipack:");
	ADD(alias, "f", क्रमmat != IPACK_ANY_FORMAT, क्रमmat);
	ADD(alias, "v", venकरोr != IPACK_ANY_ID, venकरोr);
	ADD(alias, "d", device != IPACK_ANY_ID, device);
	add_wildcard(alias);
	वापस 1;
पूर्ण

/*
 * Append a match expression क्रम a single masked hex digit.
 * outp poपूर्णांकs to a poपूर्णांकer to the अक्षरacter at which to append.
 *	*outp is updated on वापस to poपूर्णांक just after the appended text,
 *	to facilitate further appending.
 */
अटल व्योम append_nibble_mask(अक्षर **outp,
			       अचिन्हित पूर्णांक nibble, अचिन्हित पूर्णांक mask)
अणु
	अक्षर *p = *outp;
	अचिन्हित पूर्णांक i;

	चयन (mask) अणु
	हाल 0:
		*p++ = '?';
		अवरोध;

	हाल 0xf:
		p += प्र_लिखो(p, "%X",  nibble);
		अवरोध;

	शेष:
		/*
		 * Dumbly emit a match pattern क्रम all possible matching
		 * digits.  This could be improved in some हालs using ranges,
		 * but it has the advantage of being trivially correct, and is
		 * often optimal.
		 */
		*p++ = '[';
		क्रम (i = 0; i < 0x10; i++)
			अगर ((i & mask) == nibble)
				p += प्र_लिखो(p, "%X", i);
		*p++ = ']';
	पूर्ण

	/* Ensure that the string reमुख्यs NUL-terminated: */
	*p = '\0';

	/* Advance the caller's end-of-string poपूर्णांकer: */
	*outp = p;
पूर्ण

/*
 * looks like: "amba:dN"
 *
 * N is exactly 8 digits, where each is an upper-हाल hex digit, or
 *	a ? or [] pattern matching exactly one digit.
 */
अटल पूर्णांक करो_amba_entry(स्थिर अक्षर *filename,
			 व्योम *symval, अक्षर *alias)
अणु
	अचिन्हित पूर्णांक digit;
	अक्षर *p = alias;
	DEF_FIELD(symval, amba_id, id);
	DEF_FIELD(symval, amba_id, mask);

	अगर ((id & mask) != id)
		fatal("%s: Masked-off bit(s) of AMBA device ID are non-zero: "
		      "id=0x%08X, mask=0x%08X.  Please fix this driver.\n",
		      filename, id, mask);

	p += प्र_लिखो(alias, "amba:d");
	क्रम (digit = 0; digit < 8; digit++)
		append_nibble_mask(&p,
				   (id >> (4 * (7 - digit))) & 0xf,
				   (mask >> (4 * (7 - digit))) & 0xf);

	वापस 1;
पूर्ण

/*
 * looks like: "mipscdmm:tN"
 *
 * N is exactly 2 digits, where each is an upper-हाल hex digit, or
 *	a ? or [] pattern matching exactly one digit.
 */
अटल पूर्णांक करो_mips_cdmm_entry(स्थिर अक्षर *filename,
			      व्योम *symval, अक्षर *alias)
अणु
	DEF_FIELD(symval, mips_cdmm_device_id, type);

	प्र_लिखो(alias, "mipscdmm:t%02X*", type);
	वापस 1;
पूर्ण

/* LOOKS like cpu:type:x86,venVVVVfamFFFFmodMMMM:feature:*,FEAT,*
 * All fields are numbers. It would be nicer to use strings क्रम venकरोr
 * and feature, but getting those out of the build प्रणाली here is too
 * complicated.
 */

अटल पूर्णांक करो_x86cpu_entry(स्थिर अक्षर *filename, व्योम *symval,
			   अक्षर *alias)
अणु
	DEF_FIELD(symval, x86_cpu_id, feature);
	DEF_FIELD(symval, x86_cpu_id, family);
	DEF_FIELD(symval, x86_cpu_id, model);
	DEF_FIELD(symval, x86_cpu_id, venकरोr);

	म_नकल(alias, "cpu:type:x86,");
	ADD(alias, "ven", venकरोr != X86_VENDOR_ANY, venकरोr);
	ADD(alias, "fam", family != X86_FAMILY_ANY, family);
	ADD(alias, "mod", model  != X86_MODEL_ANY,  model);
	म_जोड़ो(alias, ":feature:*");
	अगर (feature != X86_FEATURE_ANY)
		प्र_लिखो(alias + म_माप(alias), "%04X*", feature);
	वापस 1;
पूर्ण

/* LOOKS like cpu:type:*:feature:*FEAT* */
अटल पूर्णांक करो_cpu_entry(स्थिर अक्षर *filename, व्योम *symval, अक्षर *alias)
अणु
	DEF_FIELD(symval, cpu_feature, feature);

	प्र_लिखो(alias, "cpu:type:*:feature:*%04X*", feature);
	वापस 1;
पूर्ण

/* Looks like: mei:S:uuid:N:* */
अटल पूर्णांक करो_mei_entry(स्थिर अक्षर *filename, व्योम *symval,
			अक्षर *alias)
अणु
	DEF_FIELD_ADDR(symval, mei_cl_device_id, name);
	DEF_FIELD_ADDR(symval, mei_cl_device_id, uuid);
	DEF_FIELD(symval, mei_cl_device_id, version);

	प्र_लिखो(alias, MEI_CL_MODULE_PREFIX);
	प्र_लिखो(alias + म_माप(alias), "%s:",  (*name)[0]  ? *name : "*");
	add_uuid(alias, *uuid);
	ADD(alias, ":", version != MEI_CL_VERSION_ANY, version);

	म_जोड़ो(alias, ":*");

	वापस 1;
पूर्ण

/* Looks like: rapidio:vNdNavNadN */
अटल पूर्णांक करो_rio_entry(स्थिर अक्षर *filename,
			व्योम *symval, अक्षर *alias)
अणु
	DEF_FIELD(symval, rio_device_id, did);
	DEF_FIELD(symval, rio_device_id, vid);
	DEF_FIELD(symval, rio_device_id, यंत्र_did);
	DEF_FIELD(symval, rio_device_id, यंत्र_vid);

	म_नकल(alias, "rapidio:");
	ADD(alias, "v", vid != RIO_ANY_ID, vid);
	ADD(alias, "d", did != RIO_ANY_ID, did);
	ADD(alias, "av", यंत्र_vid != RIO_ANY_ID, यंत्र_vid);
	ADD(alias, "ad", यंत्र_did != RIO_ANY_ID, यंत्र_did);

	add_wildcard(alias);
	वापस 1;
पूर्ण

/* Looks like: ulpi:vNpN */
अटल पूर्णांक करो_ulpi_entry(स्थिर अक्षर *filename, व्योम *symval,
			 अक्षर *alias)
अणु
	DEF_FIELD(symval, ulpi_device_id, venकरोr);
	DEF_FIELD(symval, ulpi_device_id, product);

	प्र_लिखो(alias, "ulpi:v%04xp%04x", venकरोr, product);

	वापस 1;
पूर्ण

/* Looks like: hdaudio:vNrNaN */
अटल पूर्णांक करो_hda_entry(स्थिर अक्षर *filename, व्योम *symval, अक्षर *alias)
अणु
	DEF_FIELD(symval, hda_device_id, venकरोr_id);
	DEF_FIELD(symval, hda_device_id, rev_id);
	DEF_FIELD(symval, hda_device_id, api_version);

	म_नकल(alias, "hdaudio:");
	ADD(alias, "v", venकरोr_id != 0, venकरोr_id);
	ADD(alias, "r", rev_id != 0, rev_id);
	ADD(alias, "a", api_version != 0, api_version);

	add_wildcard(alias);
	वापस 1;
पूर्ण

/* Looks like: sdw:mNpNvNcN */
अटल पूर्णांक करो_sdw_entry(स्थिर अक्षर *filename, व्योम *symval, अक्षर *alias)
अणु
	DEF_FIELD(symval, sdw_device_id, mfg_id);
	DEF_FIELD(symval, sdw_device_id, part_id);
	DEF_FIELD(symval, sdw_device_id, sdw_version);
	DEF_FIELD(symval, sdw_device_id, class_id);

	म_नकल(alias, "sdw:");
	ADD(alias, "m", mfg_id != 0, mfg_id);
	ADD(alias, "p", part_id != 0, part_id);
	ADD(alias, "v", sdw_version != 0, sdw_version);
	ADD(alias, "c", class_id != 0, class_id);

	add_wildcard(alias);
	वापस 1;
पूर्ण

/* Looks like: fsl-mc:vNdN */
अटल पूर्णांक करो_fsl_mc_entry(स्थिर अक्षर *filename, व्योम *symval,
			   अक्षर *alias)
अणु
	DEF_FIELD(symval, fsl_mc_device_id, venकरोr);
	DEF_FIELD_ADDR(symval, fsl_mc_device_id, obj_type);

	प्र_लिखो(alias, "fsl-mc:v%08Xd%s", venकरोr, *obj_type);
	वापस 1;
पूर्ण

/* Looks like: tbsvc:kSpNvNrN */
अटल पूर्णांक करो_tbsvc_entry(स्थिर अक्षर *filename, व्योम *symval, अक्षर *alias)
अणु
	DEF_FIELD(symval, tb_service_id, match_flags);
	DEF_FIELD_ADDR(symval, tb_service_id, protocol_key);
	DEF_FIELD(symval, tb_service_id, protocol_id);
	DEF_FIELD(symval, tb_service_id, protocol_version);
	DEF_FIELD(symval, tb_service_id, protocol_revision);

	म_नकल(alias, "tbsvc:");
	अगर (match_flags & TBSVC_MATCH_PROTOCOL_KEY)
		प्र_लिखो(alias + म_माप(alias), "k%s", *protocol_key);
	अन्यथा
		म_जोड़ो(alias + म_माप(alias), "k*");
	ADD(alias, "p", match_flags & TBSVC_MATCH_PROTOCOL_ID, protocol_id);
	ADD(alias, "v", match_flags & TBSVC_MATCH_PROTOCOL_VERSION,
	    protocol_version);
	ADD(alias, "r", match_flags & TBSVC_MATCH_PROTOCOL_REVISION,
	    protocol_revision);

	add_wildcard(alias);
	वापस 1;
पूर्ण

/* Looks like: typec:idNmN */
अटल पूर्णांक करो_typec_entry(स्थिर अक्षर *filename, व्योम *symval, अक्षर *alias)
अणु
	DEF_FIELD(symval, typec_device_id, svid);
	DEF_FIELD(symval, typec_device_id, mode);

	प्र_लिखो(alias, "typec:id%04X", svid);
	ADD(alias, "m", mode != TYPEC_ANY_MODE, mode);

	वापस 1;
पूर्ण

/* Looks like: tee:uuid */
अटल पूर्णांक करो_tee_entry(स्थिर अक्षर *filename, व्योम *symval, अक्षर *alias)
अणु
	DEF_FIELD(symval, tee_client_device_id, uuid);

	प्र_लिखो(alias, "tee:%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
		uuid.b[0], uuid.b[1], uuid.b[2], uuid.b[3], uuid.b[4],
		uuid.b[5], uuid.b[6], uuid.b[7], uuid.b[8], uuid.b[9],
		uuid.b[10], uuid.b[11], uuid.b[12], uuid.b[13], uuid.b[14],
		uuid.b[15]);

	add_wildcard(alias);
	वापस 1;
पूर्ण

/* Looks like: wmi:guid */
अटल पूर्णांक करो_wmi_entry(स्थिर अक्षर *filename, व्योम *symval, अक्षर *alias)
अणु
	पूर्णांक len;
	DEF_FIELD_ADDR(symval, wmi_device_id, guid_string);

	अगर (म_माप(*guid_string) != UUID_STRING_LEN) अणु
		warn("Invalid WMI device id 'wmi:%s' in '%s'\n",
				*guid_string, filename);
		वापस 0;
	पूर्ण

	len = snम_लिखो(alias, ALIAS_SIZE, WMI_MODULE_PREFIX "%s", *guid_string);
	अगर (len < 0 || len >= ALIAS_SIZE) अणु
		warn("Could not generate all MODULE_ALIAS's in '%s'\n",
				filename);
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

/* Looks like: mhi:S */
अटल पूर्णांक करो_mhi_entry(स्थिर अक्षर *filename, व्योम *symval, अक्षर *alias)
अणु
	DEF_FIELD_ADDR(symval, mhi_device_id, chan);
	प्र_लिखो(alias, MHI_DEVICE_MODALIAS_FMT, *chan);
	वापस 1;
पूर्ण

अटल पूर्णांक करो_auxiliary_entry(स्थिर अक्षर *filename, व्योम *symval, अक्षर *alias)
अणु
	DEF_FIELD_ADDR(symval, auxiliary_device_id, name);
	प्र_लिखो(alias, AUXILIARY_MODULE_PREFIX "%s", *name);

	वापस 1;
पूर्ण

/*
 * Looks like: ssam:dNcNtNiNfN
 *
 * N is exactly 2 digits, where each is an upper-हाल hex digit.
 */
अटल पूर्णांक करो_ssam_entry(स्थिर अक्षर *filename, व्योम *symval, अक्षर *alias)
अणु
	DEF_FIELD(symval, ssam_device_id, match_flags);
	DEF_FIELD(symval, ssam_device_id, करोमुख्य);
	DEF_FIELD(symval, ssam_device_id, category);
	DEF_FIELD(symval, ssam_device_id, target);
	DEF_FIELD(symval, ssam_device_id, instance);
	DEF_FIELD(symval, ssam_device_id, function);

	प्र_लिखो(alias, "ssam:d%02Xc%02X", करोमुख्य, category);
	ADD(alias, "t", match_flags & SSAM_MATCH_TARGET, target);
	ADD(alias, "i", match_flags & SSAM_MATCH_INSTANCE, instance);
	ADD(alias, "f", match_flags & SSAM_MATCH_FUNCTION, function);

	वापस 1;
पूर्ण

/* Looks like: dfl:tNfN */
अटल पूर्णांक करो_dfl_entry(स्थिर अक्षर *filename, व्योम *symval, अक्षर *alias)
अणु
	DEF_FIELD(symval, dfl_device_id, type);
	DEF_FIELD(symval, dfl_device_id, feature_id);

	प्र_लिखो(alias, "dfl:t%04Xf%04X", type, feature_id);

	add_wildcard(alias);
	वापस 1;
पूर्ण

/* Does namelen bytes of name exactly match the symbol? */
अटल bool sym_is(स्थिर अक्षर *name, अचिन्हित namelen, स्थिर अक्षर *symbol)
अणु
	अगर (namelen != म_माप(symbol))
		वापस false;

	वापस स_भेद(name, symbol, namelen) == 0;
पूर्ण

अटल व्योम करो_table(व्योम *symval, अचिन्हित दीर्घ size,
		     अचिन्हित दीर्घ id_size,
		     स्थिर अक्षर *device_id,
		     पूर्णांक (*करो_entry)(स्थिर अक्षर *filename, व्योम *symval, अक्षर *alias),
		     काष्ठा module *mod)
अणु
	अचिन्हित पूर्णांक i;
	अक्षर alias[ALIAS_SIZE];

	device_id_check(mod->name, device_id, size, id_size, symval);
	/* Leave last one: it's the terminator. */
	size -= id_size;

	क्रम (i = 0; i < size; i += id_size) अणु
		अगर (करो_entry(mod->name, symval+i, alias)) अणु
			buf_म_लिखो(&mod->dev_table_buf,
				   "MODULE_ALIAS(\"%s\");\n", alias);
		पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा devtable devtable[] = अणु
	अणु"hid", SIZE_hid_device_id, करो_hid_entryपूर्ण,
	अणु"ieee1394", SIZE_ieee1394_device_id, करो_ieee1394_entryपूर्ण,
	अणु"pci", SIZE_pci_device_id, करो_pci_entryपूर्ण,
	अणु"ccw", SIZE_ccw_device_id, करो_ccw_entryपूर्ण,
	अणु"ap", SIZE_ap_device_id, करो_ap_entryपूर्ण,
	अणु"css", SIZE_css_device_id, करो_css_entryपूर्ण,
	अणु"serio", SIZE_serio_device_id, करो_serio_entryपूर्ण,
	अणु"acpi", SIZE_acpi_device_id, करो_acpi_entryपूर्ण,
	अणु"pcmcia", SIZE_pcmcia_device_id, करो_pcmcia_entryपूर्ण,
	अणु"vio", SIZE_vio_device_id, करो_vio_entryपूर्ण,
	अणु"input", SIZE_input_device_id, करो_input_entryपूर्ण,
	अणु"eisa", SIZE_eisa_device_id, करो_eisa_entryपूर्ण,
	अणु"parisc", SIZE_parisc_device_id, करो_parisc_entryपूर्ण,
	अणु"sdio", SIZE_sdio_device_id, करो_sdio_entryपूर्ण,
	अणु"ssb", SIZE_ssb_device_id, करो_ssb_entryपूर्ण,
	अणु"bcma", SIZE_bcma_device_id, करो_bcma_entryपूर्ण,
	अणु"virtio", SIZE_virtio_device_id, करो_virtio_entryपूर्ण,
	अणु"vmbus", SIZE_hv_vmbus_device_id, करो_vmbus_entryपूर्ण,
	अणु"rpmsg", SIZE_rpmsg_device_id, करो_rpmsg_entryपूर्ण,
	अणु"i2c", SIZE_i2c_device_id, करो_i2c_entryपूर्ण,
	अणु"i3c", SIZE_i3c_device_id, करो_i3c_entryपूर्ण,
	अणु"spi", SIZE_spi_device_id, करो_spi_entryपूर्ण,
	अणु"dmi", SIZE_dmi_प्रणाली_id, करो_dmi_entryपूर्ण,
	अणु"platform", SIZE_platक्रमm_device_id, करो_platक्रमm_entryपूर्ण,
	अणु"mdio", SIZE_mdio_device_id, करो_mdio_entryपूर्ण,
	अणु"zorro", SIZE_zorro_device_id, करो_zorro_entryपूर्ण,
	अणु"isapnp", SIZE_isapnp_device_id, करो_isapnp_entryपूर्ण,
	अणु"ipack", SIZE_ipack_device_id, करो_ipack_entryपूर्ण,
	अणु"amba", SIZE_amba_id, करो_amba_entryपूर्ण,
	अणु"mipscdmm", SIZE_mips_cdmm_device_id, करो_mips_cdmm_entryपूर्ण,
	अणु"x86cpu", SIZE_x86_cpu_id, करो_x86cpu_entryपूर्ण,
	अणु"cpu", SIZE_cpu_feature, करो_cpu_entryपूर्ण,
	अणु"mei", SIZE_mei_cl_device_id, करो_mei_entryपूर्ण,
	अणु"rapidio", SIZE_rio_device_id, करो_rio_entryपूर्ण,
	अणु"ulpi", SIZE_ulpi_device_id, करो_ulpi_entryपूर्ण,
	अणु"hdaudio", SIZE_hda_device_id, करो_hda_entryपूर्ण,
	अणु"sdw", SIZE_sdw_device_id, करो_sdw_entryपूर्ण,
	अणु"fslmc", SIZE_fsl_mc_device_id, करो_fsl_mc_entryपूर्ण,
	अणु"tbsvc", SIZE_tb_service_id, करो_tbsvc_entryपूर्ण,
	अणु"typec", SIZE_typec_device_id, करो_typec_entryपूर्ण,
	अणु"tee", SIZE_tee_client_device_id, करो_tee_entryपूर्ण,
	अणु"wmi", SIZE_wmi_device_id, करो_wmi_entryपूर्ण,
	अणु"mhi", SIZE_mhi_device_id, करो_mhi_entryपूर्ण,
	अणु"auxiliary", SIZE_auxiliary_device_id, करो_auxiliary_entryपूर्ण,
	अणु"ssam", SIZE_ssam_device_id, करो_ssam_entryपूर्ण,
	अणु"dfl", SIZE_dfl_device_id, करो_dfl_entryपूर्ण,
पूर्ण;

/* Create MODULE_ALIAS() statements.
 * At this समय, we cannot ग_लिखो the actual output C source yet,
 * so we ग_लिखो पूर्णांकo the mod->dev_table_buf buffer. */
व्योम handle_moddevtable(काष्ठा module *mod, काष्ठा elf_info *info,
			Elf_Sym *sym, स्थिर अक्षर *symname)
अणु
	व्योम *symval;
	अक्षर *zeros = शून्य;
	स्थिर अक्षर *name, *identअगरier;
	अचिन्हित पूर्णांक namelen;

	/* We're looking क्रम a section relative symbol */
	अगर (!sym->st_shndx || get_secindex(info, sym) >= info->num_sections)
		वापस;

	/* We're looking क्रम an object */
	अगर (ELF_ST_TYPE(sym->st_info) != STT_OBJECT)
		वापस;

	/* All our symbols are of क्रमm __mod_<name>__<identअगरier>_device_table. */
	अगर (म_भेदन(symname, "__mod_", म_माप("__mod_")))
		वापस;
	name = symname + म_माप("__mod_");
	namelen = म_माप(name);
	अगर (namelen < म_माप("_device_table"))
		वापस;
	अगर (म_भेद(name + namelen - म_माप("_device_table"), "_device_table"))
		वापस;
	identअगरier = म_माला(name, "__");
	अगर (!identअगरier)
		वापस;
	namelen = identअगरier - name;

	/* Handle all-शून्य symbols allocated पूर्णांकo .bss */
	अगर (info->sechdrs[get_secindex(info, sym)].sh_type & SHT_NOBITS) अणु
		zeros = सुस्मृति(1, sym->st_size);
		symval = zeros;
	पूर्ण अन्यथा अणु
		symval = (व्योम *)info->hdr
			+ info->sechdrs[get_secindex(info, sym)].sh_offset
			+ sym->st_value;
	पूर्ण

	/* First handle the "special" हालs */
	अगर (sym_is(name, namelen, "usb"))
		करो_usb_table(symval, sym->st_size, mod);
	अगर (sym_is(name, namelen, "of"))
		करो_of_table(symval, sym->st_size, mod);
	अन्यथा अगर (sym_is(name, namelen, "pnp"))
		करो_pnp_device_entry(symval, sym->st_size, mod);
	अन्यथा अगर (sym_is(name, namelen, "pnp_card"))
		करो_pnp_card_entries(symval, sym->st_size, mod);
	अन्यथा अणु
		पूर्णांक i;

		क्रम (i = 0; i < ARRAY_SIZE(devtable); i++) अणु
			स्थिर काष्ठा devtable *p = &devtable[i];

			अगर (sym_is(name, namelen, p->device_id)) अणु
				करो_table(symval, sym->st_size, p->id_size,
					 p->device_id, p->करो_entry, mod);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	मुक्त(zeros);
पूर्ण

/* Now add out buffered inक्रमmation to the generated C source */
व्योम add_moddevtable(काष्ठा buffer *buf, काष्ठा module *mod)
अणु
	buf_म_लिखो(buf, "\n");
	buf_ग_लिखो(buf, mod->dev_table_buf.p, mod->dev_table_buf.pos);
	मुक्त(mod->dev_table_buf.p);
पूर्ण
