<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/tty.h>
#समावेश <linux/console.h>
#समावेश <linux/rtc.h>
#समावेश <linux/vt_kern.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/bootinfo-apollo.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/apollohw.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/machdep.h>

u_दीर्घ sio01_physaddr;
u_दीर्घ sio23_physaddr;
u_दीर्घ rtc_physaddr;
u_दीर्घ pica_physaddr;
u_दीर्घ picb_physaddr;
u_दीर्घ cpuctrl_physaddr;
u_दीर्घ समयr_physaddr;
u_दीर्घ apollo_model;

बाह्य व्योम dn_sched_init(व्योम);
बाह्य व्योम dn_init_IRQ(व्योम);
बाह्य पूर्णांक dn_dummy_hwclk(पूर्णांक, काष्ठा rtc_समय *);
बाह्य व्योम dn_dummy_reset(व्योम);
#अगर_घोषित CONFIG_HEARTBEAT
अटल व्योम dn_heartbeat(पूर्णांक on);
#पूर्ण_अगर
अटल irqवापस_t dn_समयr_पूर्णांक(पूर्णांक irq,व्योम *);
अटल व्योम dn_get_model(अक्षर *model);
अटल स्थिर अक्षर *apollo_models[] = अणु
	[APOLLO_DN3000-APOLLO_DN3000] = "DN3000 (Otter)",
	[APOLLO_DN3010-APOLLO_DN3000] = "DN3010 (Otter)",
	[APOLLO_DN3500-APOLLO_DN3000] = "DN3500 (Cougar II)",
	[APOLLO_DN4000-APOLLO_DN3000] = "DN4000 (Mink)",
	[APOLLO_DN4500-APOLLO_DN3000] = "DN4500 (Roadrunner)"
पूर्ण;

पूर्णांक __init apollo_parse_bootinfo(स्थिर काष्ठा bi_record *record)
अणु
	पूर्णांक unknown = 0;
	स्थिर व्योम *data = record->data;

	चयन (be16_to_cpu(record->tag)) अणु
	हाल BI_APOLLO_MODEL:
		apollo_model = be32_to_cpup(data);
		अवरोध;

	शेष:
		 unknown=1;
	पूर्ण

	वापस unknown;
पूर्ण

अटल व्योम __init dn_setup_model(व्योम)
अणु
	pr_info("Apollo hardware found: [%s]\n",
		apollo_models[apollo_model - APOLLO_DN3000]);

	चयन(apollo_model) अणु
		हाल APOLLO_UNKNOWN:
			panic("Unknown apollo model");
			अवरोध;
		हाल APOLLO_DN3000:
		हाल APOLLO_DN3010:
			sio01_physaddr=SAU8_SIO01_PHYSADDR;
			rtc_physaddr=SAU8_RTC_PHYSADDR;
			pica_physaddr=SAU8_PICA;
			picb_physaddr=SAU8_PICB;
			cpuctrl_physaddr=SAU8_CPUCTRL;
			समयr_physaddr=SAU8_TIMER;
			अवरोध;
		हाल APOLLO_DN4000:
			sio01_physaddr=SAU7_SIO01_PHYSADDR;
			sio23_physaddr=SAU7_SIO23_PHYSADDR;
			rtc_physaddr=SAU7_RTC_PHYSADDR;
			pica_physaddr=SAU7_PICA;
			picb_physaddr=SAU7_PICB;
			cpuctrl_physaddr=SAU7_CPUCTRL;
			समयr_physaddr=SAU7_TIMER;
			अवरोध;
		हाल APOLLO_DN4500:
			panic("Apollo model not yet supported");
			अवरोध;
		हाल APOLLO_DN3500:
			sio01_physaddr=SAU7_SIO01_PHYSADDR;
			sio23_physaddr=SAU7_SIO23_PHYSADDR;
			rtc_physaddr=SAU7_RTC_PHYSADDR;
			pica_physaddr=SAU7_PICA;
			picb_physaddr=SAU7_PICB;
			cpuctrl_physaddr=SAU7_CPUCTRL;
			समयr_physaddr=SAU7_TIMER;
			अवरोध;
		शेष:
			panic("Undefined apollo model");
			अवरोध;
	पूर्ण


पूर्ण

पूर्णांक dn_serial_console_रुको_key(काष्ठा console *co) अणु

	जबतक(!(sio01.srb_csrb & 1))
		barrier();
	वापस sio01.rhrb_thrb;
पूर्ण

व्योम dn_serial_console_ग_लिखो (काष्ठा console *co, स्थिर अक्षर *str,अचिन्हित पूर्णांक count)
अणु
   जबतक(count--) अणु
	अगर (*str == '\n') अणु
	sio01.rhrb_thrb = (अचिन्हित अक्षर)'\r';
	जबतक (!(sio01.srb_csrb & 0x4))
                ;
	पूर्ण
    sio01.rhrb_thrb = (अचिन्हित अक्षर)*str++;
    जबतक (!(sio01.srb_csrb & 0x4))
            ;
  पूर्ण
पूर्ण

व्योम dn_serial_prपूर्णांक (स्थिर अक्षर *str)
अणु
    जबतक (*str) अणु
        अगर (*str == '\n') अणु
            sio01.rhrb_thrb = (अचिन्हित अक्षर)'\r';
            जबतक (!(sio01.srb_csrb & 0x4))
                ;
        पूर्ण
        sio01.rhrb_thrb = (अचिन्हित अक्षर)*str++;
        जबतक (!(sio01.srb_csrb & 0x4))
            ;
    पूर्ण
पूर्ण

व्योम __init config_apollo(व्योम)
अणु
	पूर्णांक i;

	dn_setup_model();

	mach_sched_init=dn_sched_init; /* */
	mach_init_IRQ=dn_init_IRQ;
	mach_hwclk           = dn_dummy_hwclk; /* */
	mach_reset	     = dn_dummy_reset;  /* */
#अगर_घोषित CONFIG_HEARTBEAT
	mach_heartbeat = dn_heartbeat;
#पूर्ण_अगर
	mach_get_model       = dn_get_model;

	cpuctrl=0xaa00;

	/* clear DMA translation table */
	क्रम(i=0;i<0x400;i++)
		addr_xlat_map[i]=0;

पूर्ण

irqवापस_t dn_समयr_पूर्णांक(पूर्णांक irq, व्योम *dev_id)
अणु
	अस्थिर अचिन्हित अक्षर x;

	legacy_समयr_tick(1);
	समयr_heartbeat();

	x = *(अस्थिर अचिन्हित अक्षर *)(apollo_समयr + 3);
	x = *(अस्थिर अचिन्हित अक्षर *)(apollo_समयr + 5);

	वापस IRQ_HANDLED;
पूर्ण

व्योम dn_sched_init(व्योम)
अणु
	/* program समयr 1 */
	*(अस्थिर अचिन्हित अक्षर *)(apollo_समयr + 3) = 0x01;
	*(अस्थिर अचिन्हित अक्षर *)(apollo_समयr + 1) = 0x40;
	*(अस्थिर अचिन्हित अक्षर *)(apollo_समयr + 5) = 0x09;
	*(अस्थिर अचिन्हित अक्षर *)(apollo_समयr + 7) = 0xc4;

	/* enable IRQ of PIC B */
	*(अस्थिर अचिन्हित अक्षर *)(pica+1)&=(~8);

#अगर 0
	pr_info("*(0x10803) %02x\n",
		*(अस्थिर अचिन्हित अक्षर *)(apollo_समयr + 0x3));
	pr_info("*(0x10803) %02x\n",
		*(अस्थिर अचिन्हित अक्षर *)(apollo_समयr + 0x3));
#पूर्ण_अगर

	अगर (request_irq(IRQ_APOLLO, dn_समयr_पूर्णांक, 0, "time", शून्य))
		pr_err("Couldn't register timer interrupt\n");
पूर्ण

पूर्णांक dn_dummy_hwclk(पूर्णांक op, काष्ठा rtc_समय *t) अणु


  अगर(!op) अणु /* पढ़ो */
    t->पंचांग_sec=rtc->second;
    t->पंचांग_min=rtc->minute;
    t->पंचांग_hour=rtc->hours;
    t->पंचांग_mday=rtc->day_of_month;
    t->पंचांग_wday=rtc->day_of_week;
    t->पंचांग_mon = rtc->month - 1;
    t->पंचांग_year=rtc->year;
    अगर (t->पंचांग_year < 70)
	t->पंचांग_year += 100;
  पूर्ण अन्यथा अणु
    rtc->second=t->पंचांग_sec;
    rtc->minute=t->पंचांग_min;
    rtc->hours=t->पंचांग_hour;
    rtc->day_of_month=t->पंचांग_mday;
    अगर(t->पंचांग_wday!=-1)
      rtc->day_of_week=t->पंचांग_wday;
    rtc->month = t->पंचांग_mon + 1;
    rtc->year = t->पंचांग_year % 100;
  पूर्ण

  वापस 0;

पूर्ण

व्योम dn_dummy_reset(व्योम) अणु

  dn_serial_prपूर्णांक("The end !\n");

  क्रम(;;);

पूर्ण

व्योम dn_dummy_रुकोbut(व्योम) अणु

  dn_serial_prपूर्णांक("waitbut\n");

पूर्ण

अटल व्योम dn_get_model(अक्षर *model)
अणु
    म_नकल(model, "Apollo ");
    अगर (apollo_model >= APOLLO_DN3000 && apollo_model <= APOLLO_DN4500)
        म_जोड़ो(model, apollo_models[apollo_model - APOLLO_DN3000]);
पूर्ण

#अगर_घोषित CONFIG_HEARTBEAT
अटल पूर्णांक dn_cpuctrl=0xff00;

अटल व्योम dn_heartbeat(पूर्णांक on) अणु

	अगर(on) अणु
		dn_cpuctrl&=~0x100;
		cpuctrl=dn_cpuctrl;
	पूर्ण
	अन्यथा अणु
		dn_cpuctrl&=~0x100;
		dn_cpuctrl|=0x100;
		cpuctrl=dn_cpuctrl;
	पूर्ण
पूर्ण
#पूर्ण_अगर

