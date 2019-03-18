// 最大子数组问题
// TODO: 写成模版的形式
// TODO: 触发形式更新right, left
#include<iostream>

template<class T> 
class Sub_array{
	public:
	    int start;
	    int end;
		int mid;
	    T* array;		

		Sub_array(T *array, int start, int end); 
		Sub_array() = default;  
	    ~Sub_array(){}
		int get_mid();
        T get_sum();
		Sub_array left();
		Sub_array right();
		bool loop();
		T& operator[](int i);
};

template<class T> 
Sub_array<T>::Sub_array(T *array, int start, int end){
    this->array = array;
	this->start = start;
	this->end = end;
	mid = get_mid();
}

template<class T> 
int Sub_array<T>::get_mid(){
	return (start + end) / 2;	
}

template<class T> 
T Sub_array<T>::get_sum(){
    T sum = 0;
	for(T* i = array+start; i <= array + end; i++){
		sum += *i;		
	}
	return sum;
}

template<class T> 
Sub_array<T> Sub_array<T>::left(){
	Sub_array ret(array, start, get_mid());		
	return ret;
}

template<class T> 
Sub_array<T> Sub_array<T>::right(){
	Sub_array ret(array, get_mid() + 1, end);		
	return ret;
}

template<class T> 
bool Sub_array<T>::loop(){
	return start != end;		
}

template<class T> 
T& Sub_array<T>::operator[](int i){
	return array[i];		
}

template<class T> 
Sub_array<T> find_max_cross_subarray(Sub_array<T> array){
	//int left_sum = 1 << (sizeof(int)*8-1);
	int mid = array.get_mid();
	T left_sum = array[mid];
	array.start = mid;
	int sum = 0;
	// 依赖关系啊。。。。。。
	int temp = array.start;
	for(int i = mid; i >= temp; i--){
		sum += array[i];
		if(sum > left_sum){
			left_sum = sum;
			array.start = i;
		}	
	}
	//int right_sum = 1 << (sizeof(int)*8-1);
	sum = 0;
	temp = array.end;
	T right_sum = array[mid + 1];
	array.end = mid + 1;
	// 因为start已经改变, 所以不能用get_mid啊
	//for(int i = array.get_mid() + 1; i <= temp; i++){
	for(int i = mid + 1; i <= temp; i++){
	
		sum += array[i];
		if(sum > right_sum){
			right_sum = sum;
			array.end = i;
		}	
	}
	return array;
} 

template<class T> 
Sub_array<T> find_max_subarray(Sub_array<T> array){
    if(!array.loop()){
			return array;
	}
    int left_sum, right_sum, cross_sum;
	Sub_array<T> left, right, cross, ret_array;
	left = find_max_subarray(array.left());		
	left_sum = left.get_sum();
	right = find_max_subarray(array.right());		
	right_sum = right.get_sum();
	cross = find_max_cross_subarray(array);
	cross_sum = cross.get_sum();
	if(left_sum >= right_sum && left_sum >= cross_sum)
			ret_array = left;
	else if(right_sum >= left_sum && right_sum >= cross_sum)
			ret_array = right;
	else ret_array = cross;

	return ret_array;
}

void float_test(){
	float array[] = {13.1, -3.1, -25.1, 20.1, -3.1, -16.1, -23.1, 18.1, 20.1, -7.1, 12.1, -5.1, -22.1, 15.1, -4.1, 7.1};
	//int array[] = {1,2,3,4,5,6,7,8,9,10};
	Sub_array<float> sub_array(array, 0, sizeof(array)/sizeof(int)-1);
	Sub_array<float> result_array = find_max_subarray(sub_array);
	std::cout<<result_array.start<<" "<<result_array.end<<" "<<result_array.get_sum()<<std::endl;	
}

void int_test(){
	int array[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
	//int array[] = {1,2,3,4,5,6,7,8,9,10};
	Sub_array<int> sub_array(array, 0, sizeof(array)/sizeof(int)-1);
	Sub_array<int> result_array = find_max_subarray(sub_array);
	std::cout<<result_array.start<<" "<<result_array.end<<" "<<result_array.get_sum()<<std::endl;	
}

int main(){
	int_test();
	float_test();
	return 0;
}

