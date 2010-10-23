

/*

 	GPOUT [10, 1, -8, 2]
 	CLASS [1   1   0  0]
        for gpo in gp_out:
                tpr = fpr = 0.0
                tp = tn = fn = fp = 0.0
                for i in range(0, len(gp_out)):
                        if gp_out[i] < gpo and classes[i] == 1:
                                tp += 1.0
                        elif gp_out[i] >= gpo and classes[i] == 0:
                                tn += 1.0
                        elif gp_out[i] < gpo and classes[i] == 0:
                                fp += 1.0
                        elif gp_out[i] >= gpo and classes[i] == 1:
                                fn += 1.0
                tpr = tp / (tp + fn)
                fpr = fp / (tn + fp)
                rates.append([fpr, tpr])
                print rates
                sys.exit()   */

vector< pair<double,double> > blah(vector<double> & gp_out, vector<int> & classes) 
{
	vector< pair<double,double> > rates = new
	
	for (int i = 0; i < gp_out.size(); i++){
		
		double tpr = fpr = 0.0;		
                double tp = tn = fn = fp = 0.0;
		double gpo = gp_out[i];

		for (int j = 0; j < gp_out.size(); j++){

			if (gp_out[j] < gpo and classes[j] == 1)
                                tp += 1.0;
			else if (gp_out[j] >= gpo and classes[j] == 0)
                                tn += 1.0;
			else if (gp_out[j] < gpo and classes[j] == 0)
                                fp += 1.0;
			else if (gp_out[j] >= gpo and classes[j] == 1)
                                fn += 1.0;

		}

                tpr = tp / (tp + fn);
                fpr = fp / (tn + fp);
    		rates.push_back ( make_pair( fpr, tpr ) );
	}
	sort ( rates.begin(), rates.end() );
	return rates;
}


double area_under_curve(vector< pair<double,double> > & fpr_tpr)
{
	double auc = 0.0;
	for (int i=0; i < fpr_tpr->size()-1; i++) {
		double x1 = fpr_tpr[i].first,  y1 = fpr_tpr[i].second,
		       x2 = fpr_tpr[i+1].first,  y2 = fpr_tpr[i+1].second;
		if (y1 < y2) 
			auc += ((x2-x1)*y1 + ((x2-x1)*(y2-y1))/2);
		else
			auc += ((x2-x1)*y2 + ((x2-x1)*(y1-y2))/2);

	}
	return auc;

}
