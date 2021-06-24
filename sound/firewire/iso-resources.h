<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित SOUND_FIREWIRE_ISO_RESOURCES_H_INCLUDED
#घोषणा SOUND_FIREWIRE_ISO_RESOURCES_H_INCLUDED

#समावेश <linux/mutex.h>
#समावेश <linux/types.h>

काष्ठा fw_unit;

/**
 * काष्ठा fw_iso_resources - manages channel/bandwidth allocation
 * @channels_mask: अगर the device करोes not support all channel numbers, set this
 *                 bit mask to something अन्यथा than the शेष (all ones)
 *
 * This काष्ठाure manages (de)allocation of isochronous resources (channel and
 * bandwidth) क्रम one isochronous stream.
 */
काष्ठा fw_iso_resources अणु
	u64 channels_mask;
	/* निजी: */
	काष्ठा fw_unit *unit;
	काष्ठा mutex mutex;
	अचिन्हित पूर्णांक channel;
	अचिन्हित पूर्णांक bandwidth; /* in bandwidth units, without overhead */
	अचिन्हित पूर्णांक bandwidth_overhead;
	पूर्णांक generation; /* in which allocation is valid */
	bool allocated;
पूर्ण;

पूर्णांक fw_iso_resources_init(काष्ठा fw_iso_resources *r,
			  काष्ठा fw_unit *unit);
व्योम fw_iso_resources_destroy(काष्ठा fw_iso_resources *r);

पूर्णांक fw_iso_resources_allocate(काष्ठा fw_iso_resources *r,
			      अचिन्हित पूर्णांक max_payload_bytes, पूर्णांक speed);
पूर्णांक fw_iso_resources_update(काष्ठा fw_iso_resources *r);
व्योम fw_iso_resources_मुक्त(काष्ठा fw_iso_resources *r);

#पूर्ण_अगर
