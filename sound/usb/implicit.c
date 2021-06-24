<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
//
// Special handling क्रम implicit feedback mode
//

#समावेश <linux/init.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/audपन.स>
#समावेश <linux/usb/audio-v2.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>

#समावेश "usbaudio.h"
#समावेश "card.h"
#समावेश "helper.h"
#समावेश "implicit.h"

क्रमागत अणु
	IMPLICIT_FB_NONE,
	IMPLICIT_FB_GENERIC,
	IMPLICIT_FB_FIXED,
	IMPLICIT_FB_BOTH,	/* generic playback + capture (क्रम BOSS) */
पूर्ण;

काष्ठा snd_usb_implicit_fb_match अणु
	अचिन्हित पूर्णांक id;
	अचिन्हित पूर्णांक अगरace_class;
	अचिन्हित पूर्णांक ep_num;
	अचिन्हित पूर्णांक अगरace;
	पूर्णांक type;
पूर्ण;

#घोषणा IMPLICIT_FB_GENERIC_DEV(vend, prod) \
	अणु .id = USB_ID(vend, prod), .type = IMPLICIT_FB_GENERIC पूर्ण
#घोषणा IMPLICIT_FB_FIXED_DEV(vend, prod, ep, अगरnum) \
	अणु .id = USB_ID(vend, prod), .type = IMPLICIT_FB_FIXED, .ep_num = (ep),\
	    .अगरace = (अगरnum) पूर्ण
#घोषणा IMPLICIT_FB_BOTH_DEV(vend, prod, ep, अगरnum) \
	अणु .id = USB_ID(vend, prod), .type = IMPLICIT_FB_BOTH, .ep_num = (ep),\
	    .अगरace = (अगरnum) पूर्ण
#घोषणा IMPLICIT_FB_SKIP_DEV(vend, prod) \
	अणु .id = USB_ID(vend, prod), .type = IMPLICIT_FB_NONE पूर्ण

/* Implicit feedback quirk table क्रम playback */
अटल स्थिर काष्ठा snd_usb_implicit_fb_match playback_implicit_fb_quirks[] = अणु
	/* Generic matching */
	IMPLICIT_FB_GENERIC_DEV(0x0499, 0x1509), /* Steinberg UR22 */
	IMPLICIT_FB_GENERIC_DEV(0x0763, 0x2080), /* M-Audio FastTrack Ultra */
	IMPLICIT_FB_GENERIC_DEV(0x0763, 0x2081), /* M-Audio FastTrack Ultra */
	IMPLICIT_FB_GENERIC_DEV(0x0763, 0x2030), /* M-Audio Fast Track C400 */
	IMPLICIT_FB_GENERIC_DEV(0x0763, 0x2031), /* M-Audio Fast Track C600 */

	/* Fixed EP */
	/* FIXME: check the availability of generic matching */
	IMPLICIT_FB_FIXED_DEV(0x1397, 0x0001, 0x81, 1), /* Behringer UFX1604 */
	IMPLICIT_FB_FIXED_DEV(0x1397, 0x0002, 0x81, 1), /* Behringer UFX1204 */
	IMPLICIT_FB_FIXED_DEV(0x2466, 0x8010, 0x81, 2), /* Fractal Audio Axe-Fx III */
	IMPLICIT_FB_FIXED_DEV(0x31e9, 0x0001, 0x81, 2), /* Solid State Logic SSL2 */
	IMPLICIT_FB_FIXED_DEV(0x31e9, 0x0002, 0x81, 2), /* Solid State Logic SSL2+ */
	IMPLICIT_FB_FIXED_DEV(0x0499, 0x172f, 0x81, 2), /* Steinberg UR22C */
	IMPLICIT_FB_FIXED_DEV(0x0d9a, 0x00df, 0x81, 2), /* RTX6001 */
	IMPLICIT_FB_FIXED_DEV(0x22f0, 0x0006, 0x81, 3), /* Allen&Heath Qu-16 */
	IMPLICIT_FB_FIXED_DEV(0x1686, 0xf029, 0x82, 2), /* Zoom UAC-2 */
	IMPLICIT_FB_FIXED_DEV(0x2466, 0x8003, 0x86, 2), /* Fractal Audio Axe-Fx II */
	IMPLICIT_FB_FIXED_DEV(0x0499, 0x172a, 0x86, 2), /* Yamaha MODX */

	/* Special matching */
	अणु .id = USB_ID(0x07fd, 0x0004), .अगरace_class = USB_CLASS_AUDIO,
	  .type = IMPLICIT_FB_NONE पूर्ण,		/* MicroBook IIc */
	/* ep = 0x84, अगरnum = 0 */
	अणु .id = USB_ID(0x07fd, 0x0004), .अगरace_class = USB_CLASS_VENDOR_SPEC,
	  .type = IMPLICIT_FB_FIXED,
	  .ep_num = 0x84, .अगरace = 0 पूर्ण,		/* MOTU MicroBook II */

	अणुपूर्ण /* terminator */
पूर्ण;

/* Implicit feedback quirk table क्रम capture: only FIXED type */
अटल स्थिर काष्ठा snd_usb_implicit_fb_match capture_implicit_fb_quirks[] = अणु
	अणुपूर्ण /* terminator */
पूर्ण;

/* set up sync EP inक्रमmation on the audioक्रमmat */
अटल पूर्णांक add_implicit_fb_sync_ep(काष्ठा snd_usb_audio *chip,
				   काष्ठा audioक्रमmat *fmt,
				   पूर्णांक ep, पूर्णांक ep_idx, पूर्णांक अगरnum,
				   स्थिर काष्ठा usb_host_पूर्णांकerface *alts)
अणु
	काष्ठा usb_पूर्णांकerface *अगरace;

	अगर (!alts) अणु
		अगरace = usb_अगरnum_to_अगर(chip->dev, अगरnum);
		अगर (!अगरace || अगरace->num_altsetting < 2)
			वापस 0;
		alts = &अगरace->altsetting[1];
	पूर्ण

	fmt->sync_ep = ep;
	fmt->sync_अगरace = अगरnum;
	fmt->sync_altsetting = alts->desc.bAlternateSetting;
	fmt->sync_ep_idx = ep_idx;
	fmt->implicit_fb = 1;
	usb_audio_dbg(chip,
		      "%d:%d: added %s implicit_fb sync_ep %x, iface %d:%d\n",
		      fmt->अगरace, fmt->altsetting,
		      (ep & USB_सूची_IN) ? "playback" : "capture",
		      fmt->sync_ep, fmt->sync_अगरace, fmt->sync_altsetting);
	वापस 1;
पूर्ण

/* Check whether the given UAC2 अगरace:altset poपूर्णांकs to an implicit fb source */
अटल पूर्णांक add_generic_uac2_implicit_fb(काष्ठा snd_usb_audio *chip,
					काष्ठा audioक्रमmat *fmt,
					अचिन्हित पूर्णांक अगरnum,
					अचिन्हित पूर्णांक altsetting)
अणु
	काष्ठा usb_host_पूर्णांकerface *alts;
	काष्ठा usb_endpoपूर्णांक_descriptor *epd;

	alts = snd_usb_get_host_पूर्णांकerface(chip, अगरnum, altsetting);
	अगर (!alts)
		वापस 0;
	अगर (alts->desc.bInterfaceClass != USB_CLASS_AUDIO ||
	    alts->desc.bInterfaceSubClass != USB_SUBCLASS_AUDIOSTREAMING ||
	    alts->desc.bInterfaceProtocol != UAC_VERSION_2 ||
	    alts->desc.bNumEndpoपूर्णांकs < 1)
		वापस 0;
	epd = get_endpoपूर्णांक(alts, 0);
	अगर (!usb_endpoपूर्णांक_is_isoc_in(epd) ||
	    (epd->bmAttributes & USB_ENDPOINT_USAGE_MASK) !=
					USB_ENDPOINT_USAGE_IMPLICIT_FB)
		वापस 0;
	वापस add_implicit_fb_sync_ep(chip, fmt, epd->bEndpoपूर्णांकAddress, 0,
				       अगरnum, alts);
पूर्ण

अटल bool roland_sanity_check_अगरace(काष्ठा usb_host_पूर्णांकerface *alts)
अणु
	अगर (alts->desc.bInterfaceClass != USB_CLASS_VENDOR_SPEC ||
	    (alts->desc.bInterfaceSubClass != 2 &&
	     alts->desc.bInterfaceProtocol != 2) ||
	    alts->desc.bNumEndpoपूर्णांकs < 1)
		वापस false;
	वापस true;
पूर्ण

/* Like the UAC2 हाल above, but specअगरic to Roland with venकरोr class and hack */
अटल पूर्णांक add_roland_implicit_fb(काष्ठा snd_usb_audio *chip,
				  काष्ठा audioक्रमmat *fmt,
				  काष्ठा usb_host_पूर्णांकerface *alts)
अणु
	काष्ठा usb_endpoपूर्णांक_descriptor *epd;

	अगर (!roland_sanity_check_अगरace(alts))
		वापस 0;
	/* only when both streams are with ASYNC type */
	epd = get_endpoपूर्णांक(alts, 0);
	अगर (!usb_endpoपूर्णांक_is_isoc_out(epd) ||
	    (epd->bmAttributes & USB_ENDPOINT_SYNCTYPE) != USB_ENDPOINT_SYNC_ASYNC)
		वापस 0;

	/* check capture EP */
	alts = snd_usb_get_host_पूर्णांकerface(chip,
					  alts->desc.bInterfaceNumber + 1,
					  alts->desc.bAlternateSetting);
	अगर (!alts || !roland_sanity_check_अगरace(alts))
		वापस 0;
	epd = get_endpoपूर्णांक(alts, 0);
	अगर (!usb_endpoपूर्णांक_is_isoc_in(epd) ||
	    (epd->bmAttributes & USB_ENDPOINT_SYNCTYPE) != USB_ENDPOINT_SYNC_ASYNC)
		वापस 0;
	chip->playback_first = 1;
	वापस add_implicit_fb_sync_ep(chip, fmt, epd->bEndpoपूर्णांकAddress, 0,
				       alts->desc.bInterfaceNumber, alts);
पूर्ण

/* capture quirk क्रम Roland device; always full-duplex */
अटल पूर्णांक add_roland_capture_quirk(काष्ठा snd_usb_audio *chip,
				    काष्ठा audioक्रमmat *fmt,
				    काष्ठा usb_host_पूर्णांकerface *alts)
अणु
	काष्ठा usb_endpoपूर्णांक_descriptor *epd;

	अगर (!roland_sanity_check_अगरace(alts))
		वापस 0;
	epd = get_endpoपूर्णांक(alts, 0);
	अगर (!usb_endpoपूर्णांक_is_isoc_in(epd) ||
	    (epd->bmAttributes & USB_ENDPOINT_SYNCTYPE) != USB_ENDPOINT_SYNC_ASYNC)
		वापस 0;

	alts = snd_usb_get_host_पूर्णांकerface(chip,
					  alts->desc.bInterfaceNumber - 1,
					  alts->desc.bAlternateSetting);
	अगर (!alts || !roland_sanity_check_अगरace(alts))
		वापस 0;
	epd = get_endpoपूर्णांक(alts, 0);
	अगर (!usb_endpoपूर्णांक_is_isoc_out(epd))
		वापस 0;
	वापस add_implicit_fb_sync_ep(chip, fmt, epd->bEndpoपूर्णांकAddress, 0,
				       alts->desc.bInterfaceNumber, alts);
पूर्ण

/* Playback and capture EPs on Pioneer devices share the same अगरace/altset
 * क्रम the implicit feedback operation
 */
अटल bool is_pioneer_implicit_fb(काष्ठा snd_usb_audio *chip,
				   काष्ठा usb_host_पूर्णांकerface *alts)

अणु
	काष्ठा usb_endpoपूर्णांक_descriptor *epd;

	अगर (USB_ID_VENDOR(chip->usb_id) != 0x2b73 &&
	    USB_ID_VENDOR(chip->usb_id) != 0x08e4)
		वापस false;
	अगर (alts->desc.bInterfaceClass != USB_CLASS_VENDOR_SPEC)
		वापस false;
	अगर (alts->desc.bNumEndpoपूर्णांकs != 2)
		वापस false;

	epd = get_endpoपूर्णांक(alts, 0);
	अगर (!usb_endpoपूर्णांक_is_isoc_out(epd) ||
	    (epd->bmAttributes & USB_ENDPOINT_SYNCTYPE) != USB_ENDPOINT_SYNC_ASYNC)
		वापस false;

	epd = get_endpoपूर्णांक(alts, 1);
	अगर (!usb_endpoपूर्णांक_is_isoc_in(epd) ||
	    (epd->bmAttributes & USB_ENDPOINT_SYNCTYPE) != USB_ENDPOINT_SYNC_ASYNC ||
	    ((epd->bmAttributes & USB_ENDPOINT_USAGE_MASK) !=
	     USB_ENDPOINT_USAGE_DATA &&
	     (epd->bmAttributes & USB_ENDPOINT_USAGE_MASK) !=
	     USB_ENDPOINT_USAGE_IMPLICIT_FB))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक __add_generic_implicit_fb(काष्ठा snd_usb_audio *chip,
				     काष्ठा audioक्रमmat *fmt,
				     पूर्णांक अगरace, पूर्णांक altset)
अणु
	काष्ठा usb_host_पूर्णांकerface *alts;
	काष्ठा usb_endpoपूर्णांक_descriptor *epd;

	alts = snd_usb_get_host_पूर्णांकerface(chip, अगरace, altset);
	अगर (!alts)
		वापस 0;

	अगर ((alts->desc.bInterfaceClass != USB_CLASS_VENDOR_SPEC &&
	     alts->desc.bInterfaceClass != USB_CLASS_AUDIO) ||
	    alts->desc.bNumEndpoपूर्णांकs < 1)
		वापस 0;
	epd = get_endpoपूर्णांक(alts, 0);
	अगर (!usb_endpoपूर्णांक_is_isoc_in(epd) ||
	    (epd->bmAttributes & USB_ENDPOINT_SYNCTYPE) != USB_ENDPOINT_SYNC_ASYNC)
		वापस 0;
	वापस add_implicit_fb_sync_ep(chip, fmt, epd->bEndpoपूर्णांकAddress, 0,
				       अगरace, alts);
पूर्ण

/* More generic quirk: look क्रम the sync EP next to the data EP */
अटल पूर्णांक add_generic_implicit_fb(काष्ठा snd_usb_audio *chip,
				   काष्ठा audioक्रमmat *fmt,
				   काष्ठा usb_host_पूर्णांकerface *alts)
अणु
	अगर ((fmt->ep_attr & USB_ENDPOINT_SYNCTYPE) != USB_ENDPOINT_SYNC_ASYNC)
		वापस 0;

	अगर (__add_generic_implicit_fb(chip, fmt,
				      alts->desc.bInterfaceNumber + 1,
				      alts->desc.bAlternateSetting))
		वापस 1;
	वापस __add_generic_implicit_fb(chip, fmt,
					 alts->desc.bInterfaceNumber - 1,
					 alts->desc.bAlternateSetting);
पूर्ण

अटल स्थिर काष्ठा snd_usb_implicit_fb_match *
find_implicit_fb_entry(काष्ठा snd_usb_audio *chip,
		       स्थिर काष्ठा snd_usb_implicit_fb_match *match,
		       स्थिर काष्ठा usb_host_पूर्णांकerface *alts)
अणु
	क्रम (; match->id; match++)
		अगर (match->id == chip->usb_id &&
		    (!match->अगरace_class ||
		     (alts->desc.bInterfaceClass == match->अगरace_class)))
			वापस match;

	वापस शून्य;
पूर्ण

/* Setup an implicit feedback endpoपूर्णांक from a quirk. Returns 0 अगर no quirk
 * applies. Returns 1 अगर a quirk was found.
 */
अटल पूर्णांक audioक्रमmat_implicit_fb_quirk(काष्ठा snd_usb_audio *chip,
					 काष्ठा audioक्रमmat *fmt,
					 काष्ठा usb_host_पूर्णांकerface *alts)
अणु
	स्थिर काष्ठा snd_usb_implicit_fb_match *p;
	अचिन्हित पूर्णांक attr = fmt->ep_attr & USB_ENDPOINT_SYNCTYPE;

	p = find_implicit_fb_entry(chip, playback_implicit_fb_quirks, alts);
	अगर (p) अणु
		चयन (p->type) अणु
		हाल IMPLICIT_FB_GENERIC:
			वापस add_generic_implicit_fb(chip, fmt, alts);
		हाल IMPLICIT_FB_NONE:
			वापस 0; /* No quirk */
		हाल IMPLICIT_FB_FIXED:
			वापस add_implicit_fb_sync_ep(chip, fmt, p->ep_num, 0,
						       p->अगरace, शून्य);
		पूर्ण
	पूर्ण

	/* Special handling क्रम devices with capture quirks */
	p = find_implicit_fb_entry(chip, capture_implicit_fb_quirks, alts);
	अगर (p) अणु
		चयन (p->type) अणु
		हाल IMPLICIT_FB_FIXED:
			वापस 0; /* no quirk */
		हाल IMPLICIT_FB_BOTH:
			chip->playback_first = 1;
			वापस add_generic_implicit_fb(chip, fmt, alts);
		पूर्ण
	पूर्ण

	/* Generic UAC2 implicit feedback */
	अगर (attr == USB_ENDPOINT_SYNC_ASYNC &&
	    alts->desc.bInterfaceClass == USB_CLASS_AUDIO &&
	    alts->desc.bInterfaceProtocol == UAC_VERSION_2 &&
	    alts->desc.bNumEndpoपूर्णांकs == 1) अणु
		अगर (add_generic_uac2_implicit_fb(chip, fmt,
						 alts->desc.bInterfaceNumber + 1,
						 alts->desc.bAlternateSetting))
			वापस 1;
	पूर्ण

	/* Roland/BOSS implicit feedback with venकरोr spec class */
	अगर (USB_ID_VENDOR(chip->usb_id) == 0x0582) अणु
		अगर (add_roland_implicit_fb(chip, fmt, alts) > 0)
			वापस 1;
	पूर्ण

	/* Pioneer devices with venकरोr spec class */
	अगर (is_pioneer_implicit_fb(chip, alts)) अणु
		chip->playback_first = 1;
		वापस add_implicit_fb_sync_ep(chip, fmt,
					       get_endpoपूर्णांक(alts, 1)->bEndpoपूर्णांकAddress,
					       1, alts->desc.bInterfaceNumber,
					       alts);
	पूर्ण

	/* Try the generic implicit fb अगर available */
	अगर (chip->generic_implicit_fb)
		वापस add_generic_implicit_fb(chip, fmt, alts);

	/* No quirk */
	वापस 0;
पूर्ण

/* same क्रम capture, but only handling FIXED entry */
अटल पूर्णांक audioक्रमmat_capture_quirk(काष्ठा snd_usb_audio *chip,
				     काष्ठा audioक्रमmat *fmt,
				     काष्ठा usb_host_पूर्णांकerface *alts)
अणु
	स्थिर काष्ठा snd_usb_implicit_fb_match *p;

	p = find_implicit_fb_entry(chip, capture_implicit_fb_quirks, alts);
	अगर (p && (p->type == IMPLICIT_FB_FIXED || p->type == IMPLICIT_FB_BOTH))
		वापस add_implicit_fb_sync_ep(chip, fmt, p->ep_num, 0,
					       p->अगरace, शून्य);

	/* Roland/BOSS need full-duplex streams */
	अगर (USB_ID_VENDOR(chip->usb_id) == 0x0582) अणु
		अगर (add_roland_capture_quirk(chip, fmt, alts) > 0)
			वापस 1;
	पूर्ण

	अगर (is_pioneer_implicit_fb(chip, alts))
		वापस 1; /* skip the quirk, also करोn't handle generic sync EP */
	वापस 0;
पूर्ण

/*
 * Parse altset and set up implicit feedback endpoपूर्णांक on the audioक्रमmat
 */
पूर्णांक snd_usb_parse_implicit_fb_quirk(काष्ठा snd_usb_audio *chip,
				    काष्ठा audioक्रमmat *fmt,
				    काष्ठा usb_host_पूर्णांकerface *alts)
अणु
	अगर (fmt->endpoपूर्णांक & USB_सूची_IN)
		वापस audioक्रमmat_capture_quirk(chip, fmt, alts);
	अन्यथा
		वापस audioक्रमmat_implicit_fb_quirk(chip, fmt, alts);
पूर्ण

/*
 * Return the score of matching two audioक्रमmats.
 * Veto the audioक्रमmat अगर:
 * - It has no channels क्रम some reason.
 * - Requested PCM क्रमmat is not supported.
 * - Requested sample rate is not supported.
 */
अटल पूर्णांक match_endpoपूर्णांक_audioक्रमmats(काष्ठा snd_usb_substream *subs,
				       स्थिर काष्ठा audioक्रमmat *fp,
				       पूर्णांक rate, पूर्णांक channels,
				       snd_pcm_क्रमmat_t pcm_क्रमmat)
अणु
	पूर्णांक i, score;

	अगर (fp->channels < 1)
		वापस 0;

	अगर (!(fp->क्रमmats & pcm_क्रमmat_to_bits(pcm_क्रमmat)))
		वापस 0;

	अगर (fp->rates & SNDRV_PCM_RATE_CONTINUOUS) अणु
		अगर (rate < fp->rate_min || rate > fp->rate_max)
			वापस 0;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < fp->nr_rates; i++) अणु
			अगर (fp->rate_table[i] == rate)
				अवरोध;
		पूर्ण
		अगर (i >= fp->nr_rates)
			वापस 0;
	पूर्ण

	score = 1;
	अगर (fp->channels == channels)
		score++;

	वापस score;
पूर्ण

अटल काष्ठा snd_usb_substream *
find_matching_substream(काष्ठा snd_usb_audio *chip, पूर्णांक stream, पूर्णांक ep_num,
			पूर्णांक fmt_type)
अणु
	काष्ठा snd_usb_stream *as;
	काष्ठा snd_usb_substream *subs;

	list_क्रम_each_entry(as, &chip->pcm_list, list) अणु
		subs = &as->substream[stream];
		अगर (as->fmt_type == fmt_type && subs->ep_num == ep_num)
			वापस subs;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Return the audioक्रमmat that is suitable क्रम the implicit fb
 */
स्थिर काष्ठा audioक्रमmat *
snd_usb_find_implicit_fb_sync_क्रमmat(काष्ठा snd_usb_audio *chip,
				     स्थिर काष्ठा audioक्रमmat *target,
				     स्थिर काष्ठा snd_pcm_hw_params *params,
				     पूर्णांक stream)
अणु
	काष्ठा snd_usb_substream *subs;
	स्थिर काष्ठा audioक्रमmat *fp, *sync_fmt = शून्य;
	पूर्णांक score, high_score;

	/* Use the original audioक्रमmat as fallback क्रम the shared altset */
	अगर (target->अगरace == target->sync_अगरace &&
	    target->altsetting == target->sync_altsetting)
		sync_fmt = target;

	subs = find_matching_substream(chip, stream, target->sync_ep,
				       target->fmt_type);
	अगर (!subs)
		वापस sync_fmt;

	high_score = 0;
	list_क्रम_each_entry(fp, &subs->fmt_list, list) अणु
		score = match_endpoपूर्णांक_audioक्रमmats(subs, fp,
						    params_rate(params),
						    params_channels(params),
						    params_क्रमmat(params));
		अगर (score > high_score) अणु
			sync_fmt = fp;
			high_score = score;
		पूर्ण
	पूर्ण

	वापस sync_fmt;
पूर्ण

