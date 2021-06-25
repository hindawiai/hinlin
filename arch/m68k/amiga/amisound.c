<शैली गुरु>
/*
 * linux/arch/m68k/amiga/amisound.c
 *
 * amiga sound driver क्रम Linux/m68k
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/jअगरfies.h>
#समावेश <linux/समयr.h>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <linux/module.h>

#समावेश <यंत्र/amigahw.h>

अटल अचिन्हित लघु *snd_data;
अटल स्थिर चिन्हित अक्षर sine_data[] = अणु
	0,  39,  75,  103,  121,  127,  121,  103,  75,  39,
	0, -39, -75, -103, -121, -127, -121, -103, -75, -39
पूर्ण;
#घोषणा DATA_SIZE	ARRAY_SIZE(sine_data)

#घोषणा custom amiga_custom

    /*
     * The minimum period क्रम audio may be modअगरied by the frame buffer
     * device since it depends on htotal (क्रम OCS/ECS/AGA)
     */

अस्थिर अचिन्हित लघु amiga_audio_min_period = 124; /* Default क्रम pre-OCS */
EXPORT_SYMBOL(amiga_audio_min_period);

#घोषणा MAX_PERIOD	(65535)


    /*
     *	Current period (set by dmasound.c)
     */

अचिन्हित लघु amiga_audio_period = MAX_PERIOD;
EXPORT_SYMBOL(amiga_audio_period);

अटल अचिन्हित दीर्घ घड़ी_स्थिरant;

व्योम __init amiga_init_sound(व्योम)
अणु
	अटल काष्ठा resource beep_res = अणु .name = "Beep" पूर्ण;

	snd_data = amiga_chip_alloc_res(माप(sine_data), &beep_res);
	अगर (!snd_data) अणु
		pr_crit("amiga init_sound: failed to allocate chipmem\n");
		वापस;
	पूर्ण
	स_नकल (snd_data, sine_data, माप(sine_data));

	/* setup भागisor */
	घड़ी_स्थिरant = (amiga_colorघड़ी+DATA_SIZE/2)/DATA_SIZE;

	/* without amअगरb, turn video off and enable high quality sound */
#अगर_अघोषित CONFIG_FB_AMIGA
	amअगरb_video_off();
#पूर्ण_अगर
पूर्ण

अटल व्योम nosound(काष्ठा समयr_list *unused);
अटल DEFINE_TIMER(sound_समयr, nosound);

व्योम amiga_mksound( अचिन्हित पूर्णांक hz, अचिन्हित पूर्णांक ticks )
अणु
	अचिन्हित दीर्घ flags;

	अगर (!snd_data)
		वापस;

	local_irq_save(flags);
	del_समयr( &sound_समयr );

	अगर (hz > 20 && hz < 32767) अणु
		अचिन्हित दीर्घ period = (घड़ी_स्थिरant / hz);

		अगर (period < amiga_audio_min_period)
			period = amiga_audio_min_period;
		अगर (period > MAX_PERIOD)
			period = MAX_PERIOD;

		/* setup poपूर्णांकer to data, period, length and volume */
		custom.aud[2].audlc = snd_data;
		custom.aud[2].audlen = माप(sine_data)/2;
		custom.aud[2].audper = (अचिन्हित लघु)period;
		custom.aud[2].audvol = 32; /* 50% of maxvol */

		अगर (ticks) अणु
			sound_समयr.expires = jअगरfies + ticks;
			add_समयr( &sound_समयr );
		पूर्ण

		/* turn on DMA क्रम audio channel 2 */
		custom.dmacon = DMAF_SETCLR | DMAF_AUD2;

	पूर्ण अन्यथा
		nosound( 0 );

	local_irq_restore(flags);
पूर्ण


अटल व्योम nosound(काष्ठा समयr_list *unused)
अणु
	/* turn off DMA क्रम audio channel 2 */
	custom.dmacon = DMAF_AUD2;
	/* restore period to previous value after beeping */
	custom.aud[2].audper = amiga_audio_period;
पूर्ण
