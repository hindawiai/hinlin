<शैली गुरु>

#समावेश <यंत्र/hwrpb.h>
#समावेश <linux/device.h>


#अगर_घोषित CONFIG_SYSFS

अटल पूर्णांक cpu_is_ev6_or_later(व्योम)
अणु
	काष्ठा percpu_काष्ठा *cpu;
        अचिन्हित दीर्घ cputype;

        cpu = (काष्ठा percpu_काष्ठा *)((अक्षर *)hwrpb + hwrpb->processor_offset);
        cputype = cpu->type & 0xffffffff;
        /* Include all of EV6, EV67, EV68, EV7, EV79 and EV69. */
        वापस (cputype == EV6_CPU) || ((cputype >= EV67_CPU) && (cputype <= EV69_CPU));
पूर्ण

sमाप_प्रकार cpu_show_meltकरोwn(काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अगर (cpu_is_ev6_or_later())
		वापस प्र_लिखो(buf, "Vulnerable\n");
	अन्यथा
		वापस प्र_लिखो(buf, "Not affected\n");
पूर्ण

sमाप_प्रकार cpu_show_spectre_v1(काष्ठा device *dev,
                            काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अगर (cpu_is_ev6_or_later())
		वापस प्र_लिखो(buf, "Vulnerable\n");
	अन्यथा
		वापस प्र_लिखो(buf, "Not affected\n");
पूर्ण

sमाप_प्रकार cpu_show_spectre_v2(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अगर (cpu_is_ev6_or_later())
		वापस प्र_लिखो(buf, "Vulnerable\n");
	अन्यथा
		वापस प्र_लिखो(buf, "Not affected\n");
पूर्ण
#पूर्ण_अगर
