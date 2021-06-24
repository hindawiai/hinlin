<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Real Time Clock Driver Test Program
 *
 * Copyright (c) 2018 Alexandre Belloni <alexandre.belloni@bootlin.com>
 */

#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <linux/rtc.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <sys/ioctl.h>
#समावेश <sys/समय.स>
#समावेश <sys/types.h>
#समावेश <समय.स>
#समावेश <unistd.h>

#समावेश "../kselftest_harness.h"

#घोषणा NUM_UIE 3
#घोषणा ALARM_DELTA 3

अटल अक्षर *rtc_file = "/dev/rtc0";

FIXTURE(rtc) अणु
	पूर्णांक fd;
पूर्ण;

FIXTURE_SETUP(rtc) अणु
	self->fd = खोलो(rtc_file, O_RDONLY);
	ASSERT_NE(-1, self->fd);
पूर्ण

FIXTURE_TEARDOWN(rtc) अणु
	बंद(self->fd);
पूर्ण

TEST_F(rtc, date_पढ़ो) अणु
	पूर्णांक rc;
	काष्ठा rtc_समय rtc_पंचांग;

	/* Read the RTC समय/date */
	rc = ioctl(self->fd, RTC_RD_TIME, &rtc_पंचांग);
	ASSERT_NE(-1, rc);

	TH_LOG("Current RTC date/time is %02d/%02d/%02d %02d:%02d:%02d.",
	       rtc_पंचांग.पंचांग_mday, rtc_पंचांग.पंचांग_mon + 1, rtc_पंचांग.पंचांग_year + 1900,
	       rtc_पंचांग.पंचांग_hour, rtc_पंचांग.पंचांग_min, rtc_पंचांग.पंचांग_sec);
पूर्ण

TEST_F_TIMEOUT(rtc, uie_पढ़ो, NUM_UIE + 2) अणु
	पूर्णांक i, rc, irq = 0;
	अचिन्हित दीर्घ data;

	/* Turn on update पूर्णांकerrupts */
	rc = ioctl(self->fd, RTC_UIE_ON, 0);
	अगर (rc == -1) अणु
		ASSERT_EQ(EINVAL, त्रुटि_सं);
		TH_LOG("skip update IRQs not supported.");
		वापस;
	पूर्ण

	क्रम (i = 0; i < NUM_UIE; i++) अणु
		/* This पढ़ो will block */
		rc = पढ़ो(self->fd, &data, माप(data));
		ASSERT_NE(-1, rc);
		irq++;
	पूर्ण

	EXPECT_EQ(NUM_UIE, irq);

	rc = ioctl(self->fd, RTC_UIE_OFF, 0);
	ASSERT_NE(-1, rc);
पूर्ण

TEST_F(rtc, uie_select) अणु
	पूर्णांक i, rc, irq = 0;
	अचिन्हित दीर्घ data;

	/* Turn on update पूर्णांकerrupts */
	rc = ioctl(self->fd, RTC_UIE_ON, 0);
	अगर (rc == -1) अणु
		ASSERT_EQ(EINVAL, त्रुटि_सं);
		TH_LOG("skip update IRQs not supported.");
		वापस;
	पूर्ण

	क्रम (i = 0; i < NUM_UIE; i++) अणु
		काष्ठा समयval tv = अणु .tv_sec = 2 पूर्ण;
		fd_set पढ़ोfds;

		FD_ZERO(&पढ़ोfds);
		FD_SET(self->fd, &पढ़ोfds);
		/* The select will रुको until an RTC पूर्णांकerrupt happens. */
		rc = select(self->fd + 1, &पढ़ोfds, शून्य, शून्य, &tv);
		ASSERT_NE(-1, rc);
		ASSERT_NE(0, rc);

		/* This पढ़ो won't block */
		rc = पढ़ो(self->fd, &data, माप(अचिन्हित दीर्घ));
		ASSERT_NE(-1, rc);
		irq++;
	पूर्ण

	EXPECT_EQ(NUM_UIE, irq);

	rc = ioctl(self->fd, RTC_UIE_OFF, 0);
	ASSERT_NE(-1, rc);
पूर्ण

TEST_F(rtc, alarm_alm_set) अणु
	काष्ठा समयval tv = अणु .tv_sec = ALARM_DELTA + 2 पूर्ण;
	अचिन्हित दीर्घ data;
	काष्ठा rtc_समय पंचांग;
	fd_set पढ़ोfds;
	समय_प्रकार secs, new;
	पूर्णांक rc;

	rc = ioctl(self->fd, RTC_RD_TIME, &पंचांग);
	ASSERT_NE(-1, rc);

	secs = समयgm((काष्ठा पंचांग *)&पंचांग) + ALARM_DELTA;
	स_जमट_r(&secs, (काष्ठा पंचांग *)&पंचांग);

	rc = ioctl(self->fd, RTC_ALM_SET, &पंचांग);
	अगर (rc == -1) अणु
		ASSERT_EQ(EINVAL, त्रुटि_सं);
		TH_LOG("skip alarms are not supported.");
		वापस;
	पूर्ण

	rc = ioctl(self->fd, RTC_ALM_READ, &पंचांग);
	ASSERT_NE(-1, rc);

	TH_LOG("Alarm time now set to %02d:%02d:%02d.",
	       पंचांग.पंचांग_hour, पंचांग.पंचांग_min, पंचांग.पंचांग_sec);

	/* Enable alarm पूर्णांकerrupts */
	rc = ioctl(self->fd, RTC_AIE_ON, 0);
	ASSERT_NE(-1, rc);

	FD_ZERO(&पढ़ोfds);
	FD_SET(self->fd, &पढ़ोfds);

	rc = select(self->fd + 1, &पढ़ोfds, शून्य, शून्य, &tv);
	ASSERT_NE(-1, rc);
	ASSERT_NE(0, rc);

	/* Disable alarm पूर्णांकerrupts */
	rc = ioctl(self->fd, RTC_AIE_OFF, 0);
	ASSERT_NE(-1, rc);

	rc = पढ़ो(self->fd, &data, माप(अचिन्हित दीर्घ));
	ASSERT_NE(-1, rc);
	TH_LOG("data: %lx", data);

	rc = ioctl(self->fd, RTC_RD_TIME, &पंचांग);
	ASSERT_NE(-1, rc);

	new = समयgm((काष्ठा पंचांग *)&पंचांग);
	ASSERT_EQ(new, secs);
पूर्ण

TEST_F(rtc, alarm_wkalm_set) अणु
	काष्ठा समयval tv = अणु .tv_sec = ALARM_DELTA + 2 पूर्ण;
	काष्ठा rtc_wkalrm alarm = अणु 0 पूर्ण;
	काष्ठा rtc_समय पंचांग;
	अचिन्हित दीर्घ data;
	fd_set पढ़ोfds;
	समय_प्रकार secs, new;
	पूर्णांक rc;

	rc = ioctl(self->fd, RTC_RD_TIME, &alarm.समय);
	ASSERT_NE(-1, rc);

	secs = समयgm((काष्ठा पंचांग *)&alarm.समय) + ALARM_DELTA;
	स_जमट_r(&secs, (काष्ठा पंचांग *)&alarm.समय);

	alarm.enabled = 1;

	rc = ioctl(self->fd, RTC_WKALM_SET, &alarm);
	अगर (rc == -1) अणु
		ASSERT_EQ(EINVAL, त्रुटि_सं);
		TH_LOG("skip alarms are not supported.");
		वापस;
	पूर्ण

	rc = ioctl(self->fd, RTC_WKALM_RD, &alarm);
	ASSERT_NE(-1, rc);

	TH_LOG("Alarm time now set to %02d/%02d/%02d %02d:%02d:%02d.",
	       alarm.समय.पंचांग_mday, alarm.समय.पंचांग_mon + 1,
	       alarm.समय.पंचांग_year + 1900, alarm.समय.पंचांग_hour,
	       alarm.समय.पंचांग_min, alarm.समय.पंचांग_sec);

	FD_ZERO(&पढ़ोfds);
	FD_SET(self->fd, &पढ़ोfds);

	rc = select(self->fd + 1, &पढ़ोfds, शून्य, शून्य, &tv);
	ASSERT_NE(-1, rc);
	ASSERT_NE(0, rc);

	rc = पढ़ो(self->fd, &data, माप(अचिन्हित दीर्घ));
	ASSERT_NE(-1, rc);

	rc = ioctl(self->fd, RTC_RD_TIME, &पंचांग);
	ASSERT_NE(-1, rc);

	new = समयgm((काष्ठा पंचांग *)&पंचांग);
	ASSERT_EQ(new, secs);
पूर्ण

TEST_F_TIMEOUT(rtc, alarm_alm_set_minute, 65) अणु
	काष्ठा समयval tv = अणु .tv_sec = 62 पूर्ण;
	अचिन्हित दीर्घ data;
	काष्ठा rtc_समय पंचांग;
	fd_set पढ़ोfds;
	समय_प्रकार secs, new;
	पूर्णांक rc;

	rc = ioctl(self->fd, RTC_RD_TIME, &पंचांग);
	ASSERT_NE(-1, rc);

	secs = समयgm((काष्ठा पंचांग *)&पंचांग) + 60 - पंचांग.पंचांग_sec;
	स_जमट_r(&secs, (काष्ठा पंचांग *)&पंचांग);

	rc = ioctl(self->fd, RTC_ALM_SET, &पंचांग);
	अगर (rc == -1) अणु
		ASSERT_EQ(EINVAL, त्रुटि_सं);
		TH_LOG("skip alarms are not supported.");
		वापस;
	पूर्ण

	rc = ioctl(self->fd, RTC_ALM_READ, &पंचांग);
	ASSERT_NE(-1, rc);

	TH_LOG("Alarm time now set to %02d:%02d:%02d.",
	       पंचांग.पंचांग_hour, पंचांग.पंचांग_min, पंचांग.पंचांग_sec);

	/* Enable alarm पूर्णांकerrupts */
	rc = ioctl(self->fd, RTC_AIE_ON, 0);
	ASSERT_NE(-1, rc);

	FD_ZERO(&पढ़ोfds);
	FD_SET(self->fd, &पढ़ोfds);

	rc = select(self->fd + 1, &पढ़ोfds, शून्य, शून्य, &tv);
	ASSERT_NE(-1, rc);
	ASSERT_NE(0, rc);

	/* Disable alarm पूर्णांकerrupts */
	rc = ioctl(self->fd, RTC_AIE_OFF, 0);
	ASSERT_NE(-1, rc);

	rc = पढ़ो(self->fd, &data, माप(अचिन्हित दीर्घ));
	ASSERT_NE(-1, rc);
	TH_LOG("data: %lx", data);

	rc = ioctl(self->fd, RTC_RD_TIME, &पंचांग);
	ASSERT_NE(-1, rc);

	new = समयgm((काष्ठा पंचांग *)&पंचांग);
	ASSERT_EQ(new, secs);
पूर्ण

TEST_F_TIMEOUT(rtc, alarm_wkalm_set_minute, 65) अणु
	काष्ठा समयval tv = अणु .tv_sec = 62 पूर्ण;
	काष्ठा rtc_wkalrm alarm = अणु 0 पूर्ण;
	काष्ठा rtc_समय पंचांग;
	अचिन्हित दीर्घ data;
	fd_set पढ़ोfds;
	समय_प्रकार secs, new;
	पूर्णांक rc;

	rc = ioctl(self->fd, RTC_RD_TIME, &alarm.समय);
	ASSERT_NE(-1, rc);

	secs = समयgm((काष्ठा पंचांग *)&alarm.समय) + 60 - alarm.समय.पंचांग_sec;
	स_जमट_r(&secs, (काष्ठा पंचांग *)&alarm.समय);

	alarm.enabled = 1;

	rc = ioctl(self->fd, RTC_WKALM_SET, &alarm);
	अगर (rc == -1) अणु
		ASSERT_EQ(EINVAL, त्रुटि_सं);
		TH_LOG("skip alarms are not supported.");
		वापस;
	पूर्ण

	rc = ioctl(self->fd, RTC_WKALM_RD, &alarm);
	ASSERT_NE(-1, rc);

	TH_LOG("Alarm time now set to %02d/%02d/%02d %02d:%02d:%02d.",
	       alarm.समय.पंचांग_mday, alarm.समय.पंचांग_mon + 1,
	       alarm.समय.पंचांग_year + 1900, alarm.समय.पंचांग_hour,
	       alarm.समय.पंचांग_min, alarm.समय.पंचांग_sec);

	FD_ZERO(&पढ़ोfds);
	FD_SET(self->fd, &पढ़ोfds);

	rc = select(self->fd + 1, &पढ़ोfds, शून्य, शून्य, &tv);
	ASSERT_NE(-1, rc);
	ASSERT_NE(0, rc);

	rc = पढ़ो(self->fd, &data, माप(अचिन्हित दीर्घ));
	ASSERT_NE(-1, rc);

	rc = ioctl(self->fd, RTC_RD_TIME, &पंचांग);
	ASSERT_NE(-1, rc);

	new = समयgm((काष्ठा पंचांग *)&पंचांग);
	ASSERT_EQ(new, secs);
पूर्ण

अटल व्योम __attribute__((स्थिरructor))
__स्थिरructor_order_last(व्योम)
अणु
	अगर (!__स्थिरructor_order)
		__स्थिरructor_order = _CONSTRUCTOR_ORDER_BACKWARD;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	चयन (argc) अणु
	हाल 2:
		rtc_file = argv[1];
		/* FALLTHROUGH */
	हाल 1:
		अवरोध;
	शेष:
		ख_लिखो(मानक_त्रुटि, "usage: %s [rtcdev]\n", argv[0]);
		वापस 1;
	पूर्ण

	वापस test_harness_run(argc, argv);
पूर्ण
