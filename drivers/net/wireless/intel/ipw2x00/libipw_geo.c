<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************

  Copyright(c) 2005 Intel Corporation. All rights reserved.


  Contact Inक्रमmation:
  Intel Linux Wireless <ilw@linux.पूर्णांकel.com>
  Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497

******************************************************************************/
#समावेश <linux/compiler.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/in6.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/tcp.h>
#समावेश <linux/types.h>
#समावेश <linux/wireless.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/uaccess.h>

#समावेश "libipw.h"

पूर्णांक libipw_is_valid_channel(काष्ठा libipw_device *ieee, u8 channel)
अणु
	पूर्णांक i;

	/* Driver needs to initialize the geography map beक्रमe using
	 * these helper functions */
	अगर (ieee->geo.bg_channels == 0 && ieee->geo.a_channels == 0)
		वापस 0;

	अगर (ieee->freq_band & LIBIPW_24GHZ_BAND)
		क्रम (i = 0; i < ieee->geo.bg_channels; i++)
			/* NOTE: If G mode is currently supported but
			 * this is a B only channel, we करोn't see it
			 * as valid. */
			अगर ((ieee->geo.bg[i].channel == channel) &&
			    !(ieee->geo.bg[i].flags & LIBIPW_CH_INVALID) &&
			    (!(ieee->mode & IEEE_G) ||
			     !(ieee->geo.bg[i].flags & LIBIPW_CH_B_ONLY)))
				वापस LIBIPW_24GHZ_BAND;

	अगर (ieee->freq_band & LIBIPW_52GHZ_BAND)
		क्रम (i = 0; i < ieee->geo.a_channels; i++)
			अगर ((ieee->geo.a[i].channel == channel) &&
			    !(ieee->geo.a[i].flags & LIBIPW_CH_INVALID))
				वापस LIBIPW_52GHZ_BAND;

	वापस 0;
पूर्ण

पूर्णांक libipw_channel_to_index(काष्ठा libipw_device *ieee, u8 channel)
अणु
	पूर्णांक i;

	/* Driver needs to initialize the geography map beक्रमe using
	 * these helper functions */
	अगर (ieee->geo.bg_channels == 0 && ieee->geo.a_channels == 0)
		वापस -1;

	अगर (ieee->freq_band & LIBIPW_24GHZ_BAND)
		क्रम (i = 0; i < ieee->geo.bg_channels; i++)
			अगर (ieee->geo.bg[i].channel == channel)
				वापस i;

	अगर (ieee->freq_band & LIBIPW_52GHZ_BAND)
		क्रम (i = 0; i < ieee->geo.a_channels; i++)
			अगर (ieee->geo.a[i].channel == channel)
				वापस i;

	वापस -1;
पूर्ण

u32 libipw_channel_to_freq(काष्ठा libipw_device * ieee, u8 channel)
अणु
	स्थिर काष्ठा libipw_channel * ch;

	/* Driver needs to initialize the geography map beक्रमe using
	 * these helper functions */
	अगर (ieee->geo.bg_channels == 0 && ieee->geo.a_channels == 0)
		वापस 0;

	ch = libipw_get_channel(ieee, channel);
	अगर (!ch->channel)
		वापस 0;
	वापस ch->freq;
पूर्ण

u8 libipw_freq_to_channel(काष्ठा libipw_device * ieee, u32 freq)
अणु
	पूर्णांक i;

	/* Driver needs to initialize the geography map beक्रमe using
	 * these helper functions */
	अगर (ieee->geo.bg_channels == 0 && ieee->geo.a_channels == 0)
		वापस 0;

	freq /= 100000;

	अगर (ieee->freq_band & LIBIPW_24GHZ_BAND)
		क्रम (i = 0; i < ieee->geo.bg_channels; i++)
			अगर (ieee->geo.bg[i].freq == freq)
				वापस ieee->geo.bg[i].channel;

	अगर (ieee->freq_band & LIBIPW_52GHZ_BAND)
		क्रम (i = 0; i < ieee->geo.a_channels; i++)
			अगर (ieee->geo.a[i].freq == freq)
				वापस ieee->geo.a[i].channel;

	वापस 0;
पूर्ण

व्योम libipw_set_geo(काष्ठा libipw_device *ieee,
		      स्थिर काष्ठा libipw_geo *geo)
अणु
	स_नकल(ieee->geo.name, geo->name, 3);
	ieee->geo.name[3] = '\0';
	ieee->geo.bg_channels = geo->bg_channels;
	ieee->geo.a_channels = geo->a_channels;
	स_नकल(ieee->geo.bg, geo->bg, geo->bg_channels *
	       माप(काष्ठा libipw_channel));
	स_नकल(ieee->geo.a, geo->a, ieee->geo.a_channels *
	       माप(काष्ठा libipw_channel));
पूर्ण

स्थिर काष्ठा libipw_geo *libipw_get_geo(काष्ठा libipw_device *ieee)
अणु
	वापस &ieee->geo;
पूर्ण

u8 libipw_get_channel_flags(काष्ठा libipw_device * ieee, u8 channel)
अणु
	पूर्णांक index = libipw_channel_to_index(ieee, channel);

	अगर (index == -1)
		वापस LIBIPW_CH_INVALID;

	अगर (channel <= LIBIPW_24GHZ_CHANNELS)
		वापस ieee->geo.bg[index].flags;

	वापस ieee->geo.a[index].flags;
पूर्ण

अटल स्थिर काष्ठा libipw_channel bad_channel = अणु
	.channel = 0,
	.flags = LIBIPW_CH_INVALID,
	.max_घातer = 0,
पूर्ण;

स्थिर काष्ठा libipw_channel *libipw_get_channel(काष्ठा libipw_device
						      *ieee, u8 channel)
अणु
	पूर्णांक index = libipw_channel_to_index(ieee, channel);

	अगर (index == -1)
		वापस &bad_channel;

	अगर (channel <= LIBIPW_24GHZ_CHANNELS)
		वापस &ieee->geo.bg[index];

	वापस &ieee->geo.a[index];
पूर्ण

EXPORT_SYMBOL(libipw_get_channel);
EXPORT_SYMBOL(libipw_get_channel_flags);
EXPORT_SYMBOL(libipw_is_valid_channel);
EXPORT_SYMBOL(libipw_freq_to_channel);
EXPORT_SYMBOL(libipw_channel_to_freq);
EXPORT_SYMBOL(libipw_channel_to_index);
EXPORT_SYMBOL(libipw_set_geo);
EXPORT_SYMBOL(libipw_get_geo);
