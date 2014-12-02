# Давайте реализуем метод имитации отжига на Руби
module AI_Lab1
	ANNEALING_MAX_ITERATIONS = 10000
	ANNEALING_TEMP_RADIUS = 0.7

	def self.rand_float_in(range)
		return rand * (range.max - range.min) + range.min
	end
	
	def self.get_random_point_in(search_area)
		point = []
		search_area.each { |range| point.push(rand_float_in range) }
		return point
	end
	
	def self.dist(a, b)
		sum_sq = 0
		a.each_index { |i| sum_sq += (a[i] - b[i]) ** 2 }
		return Math.sqrt(sum_sq)
	end
	
	def self.get_candidate(cur_point, temp, search_area)
		radius = temp * ANNEALING_TEMP_RADIUS
		
		area = search_area.dup
		area.each_index do |i|
			area[i] = ((cur_point[i] - radius / 2)..(cur_point[i] + radius / 2))
		end
		
		begin
			point = get_random_point_in area
		end until dist(point, cur_point) < radius
		return point
	end
	
	def self.transition_probability(delta_energy, temp)
		return Math.exp( -delta_energy.to_f / temp )
	end
	
	def self.get_temp(start_temp, iteration_number)
		return start_temp.to_f / iteration_number
		#return start_temp.to_f / Math.log(iteration_number + 1) 
	end
	
	# Метод изначально создавался способным обрабатывать функции с произвольным числом параметров 
	def self.annealing_simulation(f, search_area, start_temp, min_temp, start_point = nil)
		# 1. выбираем начальную точку
		if start_point == nil 
			start_point = get_random_point_in search_area
		end
		
		graph_info = [] # вектор из чисел: значение минимума на i-той итерации
		
		# Считаем значение функции в начальной точке
		cur_state  = start_point
		cur_energy = f[*cur_state]
		cur_temp = start_temp
		
		graph_info << cur_energy
		
		(1..ANNEALING_MAX_ITERATIONS).each do |iter|
			# В цикле
			# В качестве кандидата на роль следующей точки возьмем случайную точку
			# интересно что даже в таком примитивном варианте метод отжига хорошо работает
			candidate_state  = get_candidate(cur_state, cur_temp, search_area)
			candidate_energy = f[*candidate_state]
			
			if (candidate_energy < cur_energy) || (rand < transition_probability( candidate_energy - cur_energy, cur_temp ))
				cur_state  = candidate_state
				cur_energy = candidate_energy
			end
			
			graph_info << cur_energy
			
			# Уменьшаем температуру
			cur_temp = get_temp(start_temp, iter)
			
			break if cur_temp <= min_temp
		end
		
		return { :answer        => cur_state, 
				 :minimum_value => f[*cur_state], 
				 :iterations    => graph_info.size, 
				 :graph_info    => graph_info }
	end
end

f = -> x, y { (x - 5)**2 + (y + 1)**2 - 7 }

area = [ (-10.0..10.0), (-10.0..10.0) ]

results = AI_Lab1.annealing_simulation(f, area, 50, 0.01)
p results[:answer]
p results[:minimum_value]
p results[:iterations]