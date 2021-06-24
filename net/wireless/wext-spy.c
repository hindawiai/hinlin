<शैली गुरु>
/*
 * This file implement the Wireless Extensions spy API.
 *
 * Authors :	Jean Tourrilhes - HPL - <jt@hpl.hp.com>
 * Copyright (c) 1997-2007 Jean Tourrilhes, All Rights Reserved.
 *
 * (As all part of the Linux kernel, this file is GPL)
 */

#समावेश <linux/wireless.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/export.h>
#समावेश <net/iw_handler.h>
#समावेश <net/arp.h>
#समावेश <net/wext.h>

अटल अंतरभूत काष्ठा iw_spy_data *get_spydata(काष्ठा net_device *dev)
अणु
	/* This is the new way */
	अगर (dev->wireless_data)
		वापस dev->wireless_data->spy_data;
	वापस शून्य;
पूर्ण

पूर्णांक iw_handler_set_spy(काष्ठा net_device *	dev,
		       काष्ठा iw_request_info *	info,
		       जोड़ iwreq_data *	wrqu,
		       अक्षर *			extra)
अणु
	काष्ठा iw_spy_data *	spydata = get_spydata(dev);
	काष्ठा sockaddr *	address = (काष्ठा sockaddr *) extra;

	/* Make sure driver is not buggy or using the old API */
	अगर (!spydata)
		वापस -EOPNOTSUPP;

	/* Disable spy collection जबतक we copy the addresses.
	 * While we copy addresses, any call to wireless_spy_update()
	 * will NOP. This is OK, as anyway the addresses are changing. */
	spydata->spy_number = 0;

	/* We want to operate without locking, because wireless_spy_update()
	 * most likely will happen in the पूर्णांकerrupt handler, and thereक्रमe
	 * have its own locking स्थिरraपूर्णांकs and needs perक्रमmance.
	 * The rtnl_lock() make sure we करोn't race with the other iw_handlers.
	 * This make sure wireless_spy_update() "see" that the spy list
	 * is temporarily disabled. */
	smp_wmb();

	/* Are there are addresses to copy? */
	अगर (wrqu->data.length > 0) अणु
		पूर्णांक i;

		/* Copy addresses */
		क्रम (i = 0; i < wrqu->data.length; i++)
			स_नकल(spydata->spy_address[i], address[i].sa_data,
			       ETH_ALEN);
		/* Reset stats */
		स_रखो(spydata->spy_stat, 0,
		       माप(काष्ठा iw_quality) * IW_MAX_SPY);
	पूर्ण

	/* Make sure above is updated beक्रमe re-enabling */
	smp_wmb();

	/* Enable addresses */
	spydata->spy_number = wrqu->data.length;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(iw_handler_set_spy);

पूर्णांक iw_handler_get_spy(काष्ठा net_device *	dev,
		       काष्ठा iw_request_info *	info,
		       जोड़ iwreq_data *	wrqu,
		       अक्षर *			extra)
अणु
	काष्ठा iw_spy_data *	spydata = get_spydata(dev);
	काष्ठा sockaddr *	address = (काष्ठा sockaddr *) extra;
	पूर्णांक			i;

	/* Make sure driver is not buggy or using the old API */
	अगर (!spydata)
		वापस -EOPNOTSUPP;

	wrqu->data.length = spydata->spy_number;

	/* Copy addresses. */
	क्रम (i = 0; i < spydata->spy_number; i++) 	अणु
		स_नकल(address[i].sa_data, spydata->spy_address[i], ETH_ALEN);
		address[i].sa_family = AF_UNIX;
	पूर्ण
	/* Copy stats to the user buffer (just after). */
	अगर (spydata->spy_number > 0)
		स_नकल(extra  + (माप(काष्ठा sockaddr) *spydata->spy_number),
		       spydata->spy_stat,
		       माप(काष्ठा iw_quality) * spydata->spy_number);
	/* Reset updated flags. */
	क्रम (i = 0; i < spydata->spy_number; i++)
		spydata->spy_stat[i].updated &= ~IW_QUAL_ALL_UPDATED;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(iw_handler_get_spy);

/*------------------------------------------------------------------*/
/*
 * Standard Wireless Handler : set spy threshold
 */
पूर्णांक iw_handler_set_thrspy(काष्ठा net_device *	dev,
			  काष्ठा iw_request_info *info,
			  जोड़ iwreq_data *	wrqu,
			  अक्षर *		extra)
अणु
	काष्ठा iw_spy_data *	spydata = get_spydata(dev);
	काष्ठा iw_thrspy *	threshold = (काष्ठा iw_thrspy *) extra;

	/* Make sure driver is not buggy or using the old API */
	अगर (!spydata)
		वापस -EOPNOTSUPP;

	/* Just करो it */
	स_नकल(&(spydata->spy_thr_low), &(threshold->low),
	       2 * माप(काष्ठा iw_quality));

	/* Clear flag */
	स_रखो(spydata->spy_thr_under, '\0', माप(spydata->spy_thr_under));

	वापस 0;
पूर्ण
EXPORT_SYMBOL(iw_handler_set_thrspy);

/*------------------------------------------------------------------*/
/*
 * Standard Wireless Handler : get spy threshold
 */
पूर्णांक iw_handler_get_thrspy(काष्ठा net_device *	dev,
			  काष्ठा iw_request_info *info,
			  जोड़ iwreq_data *	wrqu,
			  अक्षर *		extra)
अणु
	काष्ठा iw_spy_data *	spydata = get_spydata(dev);
	काष्ठा iw_thrspy *	threshold = (काष्ठा iw_thrspy *) extra;

	/* Make sure driver is not buggy or using the old API */
	अगर (!spydata)
		वापस -EOPNOTSUPP;

	/* Just करो it */
	स_नकल(&(threshold->low), &(spydata->spy_thr_low),
	       2 * माप(काष्ठा iw_quality));

	वापस 0;
पूर्ण
EXPORT_SYMBOL(iw_handler_get_thrspy);

/*------------------------------------------------------------------*/
/*
 * Prepare and send a Spy Threshold event
 */
अटल व्योम iw_send_thrspy_event(काष्ठा net_device *	dev,
				 काष्ठा iw_spy_data *	spydata,
				 अचिन्हित अक्षर *	address,
				 काष्ठा iw_quality *	wstats)
अणु
	जोड़ iwreq_data	wrqu;
	काष्ठा iw_thrspy	threshold;

	/* Init */
	wrqu.data.length = 1;
	wrqu.data.flags = 0;
	/* Copy address */
	स_नकल(threshold.addr.sa_data, address, ETH_ALEN);
	threshold.addr.sa_family = ARPHRD_ETHER;
	/* Copy stats */
	स_नकल(&(threshold.qual), wstats, माप(काष्ठा iw_quality));
	/* Copy also thresholds */
	स_नकल(&(threshold.low), &(spydata->spy_thr_low),
	       2 * माप(काष्ठा iw_quality));

	/* Send event to user space */
	wireless_send_event(dev, SIOCGIWTHRSPY, &wrqu, (अक्षर *) &threshold);
पूर्ण

/* ---------------------------------------------------------------- */
/*
 * Call क्रम the driver to update the spy data.
 * For now, the spy data is a simple array. As the size of the array is
 * small, this is good enough. If we wanted to support larger number of
 * spy addresses, we should use something more efficient...
 */
व्योम wireless_spy_update(काष्ठा net_device *	dev,
			 अचिन्हित अक्षर *	address,
			 काष्ठा iw_quality *	wstats)
अणु
	काष्ठा iw_spy_data *	spydata = get_spydata(dev);
	पूर्णांक			i;
	पूर्णांक			match = -1;

	/* Make sure driver is not buggy or using the old API */
	अगर (!spydata)
		वापस;

	/* Update all records that match */
	क्रम (i = 0; i < spydata->spy_number; i++)
		अगर (ether_addr_equal(address, spydata->spy_address[i])) अणु
			स_नकल(&(spydata->spy_stat[i]), wstats,
			       माप(काष्ठा iw_quality));
			match = i;
		पूर्ण

	/* Generate an event अगर we cross the spy threshold.
	 * To aव्योम event storms, we have a simple hysteresis : we generate
	 * event only when we go under the low threshold or above the
	 * high threshold. */
	अगर (match >= 0) अणु
		अगर (spydata->spy_thr_under[match]) अणु
			अगर (wstats->level > spydata->spy_thr_high.level) अणु
				spydata->spy_thr_under[match] = 0;
				iw_send_thrspy_event(dev, spydata,
						     address, wstats);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (wstats->level < spydata->spy_thr_low.level) अणु
				spydata->spy_thr_under[match] = 1;
				iw_send_thrspy_event(dev, spydata,
						     address, wstats);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(wireless_spy_update);
