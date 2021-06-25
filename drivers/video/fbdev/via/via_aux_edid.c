<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2011 Florian Tobias Schandinat <FlorianSchandinat@gmx.de>
 */
/*
 * generic EDID driver
 */

#समावेश <linux/slab.h>
#समावेश <linux/fb.h>
#समावेश "via_aux.h"
#समावेश "../edid.h"


अटल स्थिर अक्षर *name = "EDID";


अटल व्योम query_edid(काष्ठा via_aux_drv *drv)
अणु
	काष्ठा fb_monspecs *spec = drv->data;
	अचिन्हित अक्षर edid[EDID_LENGTH];
	bool valid = false;

	अगर (spec) अणु
		fb_destroy_modedb(spec->modedb);
	पूर्ण अन्यथा अणु
		spec = kदो_स्मृति(माप(*spec), GFP_KERNEL);
		अगर (!spec)
			वापस;
	पूर्ण

	spec->version = spec->revision = 0;
	अगर (via_aux_पढ़ो(drv, 0x00, edid, EDID_LENGTH)) अणु
		fb_edid_to_monspecs(edid, spec);
		valid = spec->version || spec->revision;
	पूर्ण

	अगर (!valid) अणु
		kमुक्त(spec);
		spec = शून्य;
	पूर्ण अन्यथा
		prपूर्णांकk(KERN_DEBUG "EDID: %s %s\n", spec->manufacturer, spec->monitor);

	drv->data = spec;
पूर्ण

अटल स्थिर काष्ठा fb_videomode *get_preferred_mode(काष्ठा via_aux_drv *drv)
अणु
	काष्ठा fb_monspecs *spec = drv->data;
	पूर्णांक i;

	अगर (!spec || !spec->modedb || !(spec->misc & FB_MISC_1ST_DETAIL))
		वापस शून्य;

	क्रम (i = 0; i < spec->modedb_len; i++) अणु
		अगर (spec->modedb[i].flag & FB_MODE_IS_FIRST &&
			spec->modedb[i].flag & FB_MODE_IS_DETAILED)
			वापस &spec->modedb[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम cleanup(काष्ठा via_aux_drv *drv)
अणु
	काष्ठा fb_monspecs *spec = drv->data;

	अगर (spec)
		fb_destroy_modedb(spec->modedb);
पूर्ण

व्योम via_aux_edid_probe(काष्ठा via_aux_bus *bus)
अणु
	काष्ठा via_aux_drv drv = अणु
		.bus	=	bus,
		.addr	=	0x50,
		.name	=	name,
		.cleanup	=	cleanup,
		.get_preferred_mode	=	get_preferred_modeपूर्ण;

	query_edid(&drv);

	/* as EDID devices can be connected/disconnected just add the driver */
	via_aux_add(&drv);
पूर्ण
