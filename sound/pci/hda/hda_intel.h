<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 */
#अगर_अघोषित __SOUND_HDA_INTEL_H
#घोषणा __SOUND_HDA_INTEL_H

#समावेश "hda_controller.h"

काष्ठा hda_पूर्णांकel अणु
	काष्ठा azx chip;

	/* क्रम pending irqs */
	काष्ठा work_काष्ठा irq_pending_work;

	/* sync probing */
	काष्ठा completion probe_रुको;
	काष्ठा work_काष्ठा probe_work;

	/* card list (क्रम घातer_save trigger) */
	काष्ठा list_head list;

	/* extra flags */
	अचिन्हित पूर्णांक irq_pending_warned:1;
	अचिन्हित पूर्णांक probe_जारीd:1;

	/* vga_चयनeroo setup */
	अचिन्हित पूर्णांक use_vga_चयनeroo:1;
	अचिन्हित पूर्णांक vga_चयनeroo_रेजिस्टरed:1;
	अचिन्हित पूर्णांक init_failed:1; /* delayed init failed */
	अचिन्हित पूर्णांक मुक्तd:1; /* resources alपढ़ोy released */

	bool need_i915_घातer:1; /* the hda controller needs i915 घातer */
पूर्ण;

#पूर्ण_अगर
