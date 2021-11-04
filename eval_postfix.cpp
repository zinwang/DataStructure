//expression tree infix to posfix, and evaluate the expression 

#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <map>
#include <algorithm>

std::map <char,int> tbl={{')',0},{'(',0},{'+',1},{'-',1},{'*',2},{'/',2},{'%',2}};

std::map <char,int> opr_tbl={{'+',1},{'-',2},{'*',3},{'/',4},{'%',5}};



std::string conversion(std::string infx_str){
	int len=infx_str.length();
	std::stack <char> opr_stk;
	std::string ans="";
	for(int i=0;i<len;i++){
		//std::cout<<ans<<"\n";
		char ctmp=infx_str[i];
		if(ctmp>='0' && ctmp<='9'){ //if ctmp is numeral, just add to ans
			ans+=ctmp;
			char nxt_char=infx_str[i+1];
			if(nxt_char<'0' || nxt_char>'9'){
				ans+=" ";
			}
		}else if(ctmp==')'){ // if ctmp is ')', pop opr_stk until '(' 
			while(opr_stk.top()!='('){
				ans+=opr_stk.top();
				ans+=" ";
				opr_stk.pop();	
			}
			opr_stk.pop(); //pop the '('
		}else{ 
			bool ctmp_pri_gt_ostk_top=0; //bool var standing for ctmp prority greater than opr_stk.top()
			if(tbl.count(ctmp) && !opr_stk.empty()){
				ctmp_pri_gt_ostk_top = tbl[ctmp] > tbl[opr_stk.top()];
			}
			if(!( ctmp=='(' || opr_stk.empty() || ctmp_pri_gt_ostk_top )){ 
				//if ctmp=='(' or opr_stk is empty or the priority of ctmp is higher than that of opr_stk.top(), the program will not go in to this condition and only do the opr_stk.push down below.
				ans+=opr_stk.top();
				ans+=" ";
				opr_stk.pop();
			
			}
			opr_stk.push(ctmp); 
		}
	
	}

	while(!opr_stk.empty()){ //add the remains in the stack to ans
		ans+=opr_stk.top();
		if(opr_stk.size()>1){
			ans+=" ";
		}
		opr_stk.pop();	
	}
	return ans;


}




bool verify_expr(std::string s){
	int len=s.length();
	int cnt=0;
	char prev_char='\0';
	for(int i=0;i<len;i++){
		char ctmp=s[i];
		if(ctmp=='('){
			cnt+=1;		
		}else if(ctmp==')'){
			cnt+=-1;
		}
		
		if(tbl.count(ctmp)){
			if(tbl[ctmp]==2 && i==0){
				//std::cout<<"test1\n";
				return 0;
			}
		}else if( (ctmp <'0' || ctmp >'9') && ctmp!=' ' && ctmp!='\n'){
			//std::cout<<int(ctmp)<<":"<<i<<" test2\n";
			return 0;
		}
		
		if(tbl.count(ctmp) && tbl.count(prev_char)){
			if(tbl[ctmp]>0 && tbl[prev_char]>0){
				//std::cout<<"test3\n";
				return 0;
			}
		}

		if(cnt<0){
			//std::cout<<"test4\n";
			return 0;
		}
		prev_char=ctmp;
	
	}

	return cnt==0;


}




int eval_value(std::string pfx_str){
	std::stack <int> value_stk;
	std::istringstream tmp_stream(pfx_str);
	std::string stmp;
	while(std::getline(tmp_stream,stmp,' ')){
		//std::cout<<stmp<<"\n";
		if(stmp.length()==1){
			char ctmp = stmp[0];
			if(opr_tbl.count(ctmp)){
				int a = value_stk.top();
				value_stk.pop();
				int b = value_stk.top();
				value_stk.pop();
				int value_tmp;
				switch(opr_tbl[ctmp]){
					case 1: //+
						value_tmp = a + b;
						break;
					case 2: //-
						value_tmp = b - a;
						break;
					case 3: //*
						value_tmp = a * b;
						break;
					case 4: // /
						value_tmp = b / a;
						break;
					case 5: //%
						value_tmp = b % a;		
						break;
				}
				value_stk.push(value_tmp);
				continue;		
			}
		}
		int itmp = std::stoi(stmp);
		//std::cout<<itmp<<"\n";
		value_stk.push(itmp);
		
	}
	int ans = value_stk.top();
	value_stk.pop();
	return ans;


}






int main(){
	std::string s;
	std::getline(std::cin,s);
	//std::cout<<eval_value(s)<<"\n";	

	//erase space in s
	std::string::iterator end_pos = std::remove_if(s.begin(),s.end(),isspace);
	s.erase(end_pos,s.end());

	//std::cout<<conversion(s)<<"\n";
	//std::cout<<verify_expr(s)<<"\n";
	if(verify_expr(s)){
		std::cout<<conversion(s)<<"\n";
		std::cout<<eval_value(conversion(s))<<"\n";

	}else{
		std::cout<<"The input expression is not valid!\n";
	}
	



	return 0;
}
