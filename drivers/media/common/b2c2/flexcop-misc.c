<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Linux driver क्रम digital TV devices equipped with B2C2 FlexcopII(b)/III
 * flexcop-misc.c - miscellaneous functions
 * see flexcop.c क्रम copyright inक्रमmation
 */
#समावेश "flexcop.h"

व्योम flexcop_determine_revision(काष्ठा flexcop_device *fc)
अणु
	flexcop_ibi_value v = fc->पढ़ो_ibi_reg(fc,misc_204);

	चयन (v.misc_204.Rev_N_sig_revision_hi) अणु
	हाल 0x2:
		deb_info("found a FlexCopII.\n");
		fc->rev = FLEXCOP_II;
		अवरोध;
	हाल 0x3:
		deb_info("found a FlexCopIIb.\n");
		fc->rev = FLEXCOP_IIB;
		अवरोध;
	हाल 0x0:
		deb_info("found a FlexCopIII.\n");
		fc->rev = FLEXCOP_III;
		अवरोध;
	शेष:
		err("unknown FlexCop Revision: %x. Please report this to linux-dvb@linuxtv.org.",
				v.misc_204.Rev_N_sig_revision_hi);
		अवरोध;
	पूर्ण

	अगर ((fc->has_32_hw_pid_filter = v.misc_204.Rev_N_sig_caps))
		deb_info("this FlexCop has the additional 32 hardware pid filter.\n");
	अन्यथा
		deb_info("this FlexCop has the 6 basic main hardware pid filter.\n");
	/* bus parts have to decide अगर hw pid filtering is used or not. */
पूर्ण

अटल स्थिर अक्षर *flexcop_revision_names[] = अणु
	"Unknown chip",
	"FlexCopII",
	"FlexCopIIb",
	"FlexCopIII",
पूर्ण;

अटल स्थिर अक्षर *flexcop_device_names[] = अणु
	[FC_UNK]	= "Unknown device",
	[FC_CABLE]	= "Cable2PC/CableStar 2 DVB-C",
	[FC_AIR_DVBT]	= "Air2PC/AirStar 2 DVB-T",
	[FC_AIR_ATSC1]	= "Air2PC/AirStar 2 ATSC 1st generation",
	[FC_AIR_ATSC2]	= "Air2PC/AirStar 2 ATSC 2nd generation",
	[FC_AIR_ATSC3]	= "Air2PC/AirStar 2 ATSC 3rd generation (HD5000)",
	[FC_SKY_REV23]	= "Sky2PC/SkyStar 2 DVB-S rev 2.3 (old version)",
	[FC_SKY_REV26]	= "Sky2PC/SkyStar 2 DVB-S rev 2.6",
	[FC_SKY_REV27]	= "Sky2PC/SkyStar 2 DVB-S rev 2.7a/u",
	[FC_SKY_REV28]	= "Sky2PC/SkyStar 2 DVB-S rev 2.8",
	[FC_SKYS2_REV33] = "Sky2PC/SkyStar S2 DVB-S/S2 rev 3.3",
पूर्ण;

अटल स्थिर अक्षर *flexcop_bus_names[] = अणु
	"USB",
	"PCI",
पूर्ण;

व्योम flexcop_device_name(काष्ठा flexcop_device *fc,
		स्थिर अक्षर *prefix, स्थिर अक्षर *suffix)
अणु
	info("%s '%s' at the '%s' bus controlled by a '%s' %s",
			prefix,	flexcop_device_names[fc->dev_type],
			flexcop_bus_names[fc->bus_type],
			flexcop_revision_names[fc->rev], suffix);
पूर्ण

व्योम flexcop_dump_reg(काष्ठा flexcop_device *fc,
		flexcop_ibi_रेजिस्टर reg, पूर्णांक num)
अणु
	flexcop_ibi_value v;
	पूर्णांक i;
	क्रम (i = 0; i < num; i++) अणु
		v = fc->पढ़ो_ibi_reg(fc, reg+4*i);
		deb_rdump("0x%03x: %08x, ", reg+4*i, v.raw);
	पूर्ण
	deb_rdump("\n");
पूर्ण
EXPORT_SYMBOL(flexcop_dump_reg);
